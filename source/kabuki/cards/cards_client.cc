﻿/** kabuki::cards
    @file    ~/source/kabuki/cards/cards_card_game.cc
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <calemccollough.github.io>;
             All right reserved (R). Licensed under the Apache License, Version 
             2.0 (the "License"); you may not use this file except in 
             compliance with the License. You may obtain a copy of the License 
             [here](http://www.apache.org/licenses/LICENSE-2.0). Unless 
             required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS,
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
             implied. See the License for the specific language governing 
             permissions and limitations under the License.
*/

#include "client.h"

using namespace _;
using namespace kabuki::id;
using namespace std;

namespace kabuki { namespace cards {

Client::Client ():
    state_ (0),
    user_  (),
    pack_  (){
}

Client::~Client () {
    DeleteRemotePlayers ();
}

void Client::DeleteRemotePlayers () {
    for (int i = players_.GetCount (); i > 0; --i) {
        RemotePlayer* player = players_.Pop ();
        delete player;
    }
}

uint Client::GetState () {
    return state_;
}

bool Client::SetState (int state) {
    if (state < 0) {
        return false;
    }
    state_ = state;
    return true;
}

void Client::PrintPlayers () {
    for (int i = 0; i < players_.GetCount (); ++i) {
        players_[i]->Print ();
    }
}

void Client::PrintRoundStatsString () {
    PrintLine ("|", '~');
    cout << "Round: " << round_number_ << "\n";


    PrintLine ("> ", '~');
}

void Client::Print () {
    PrintLine (" ", '_');
    cout << "\n| " << game_name_
         << "\n| Num Players : " << players_.GetCount () 
         << " Max: " << players_.GetSize ()
         << "\n| Round Number: " << round_number_
         << "\n| Num Players : " << players_.GetCount ();

    PrintPlayers ();
    PrintLine ("|", '_');
}

const Operation* Client::Star (uint index, _::Expression* expr) {
    static const Operation This = { "CardsClient",
        NumOperations (0), FirstOperation ('A'),
        "kabuki::cards Script client.", 0
    };
    void* args[4];
    RemotePlayer* player;
    switch (index) {
        case '?': return &This;
        case 'A': {
            static const Operation OpA = { "SetState",
                Params<1, UI1> (), Params<0> (),
                "Sets the client state.", 0
            };
            if (!expr) return &OpA;
            byte state;
            if (!ExprArgs (expr, Params<1, UI1> (), Args (args, &state)))
                return expr->result;
            SetState (state);
            return nullptr;
        }
        case 'B': {
            static const Operation OpB = { "Print",
                Params<1, STX, kMaxMessageLength + 1> (), Params<0> (),
                "Sets the client state.", 0
            };
            if (!expr) return &OpB;
            char buffer[kMaxMessageLength + 1];
            if (!ExprArgs (expr, Params<1, STX, kMaxMessageLength + 1> (),
                           Args (args, buffer)))
                return expr->result;
            cout << buffer;
            return nullptr;
        }
        case 'C': {
            static const uint_t* kRxHeaderC = Params<1, SI4,
                STX, User::kDefaultMaxDislpayNameLength + 1,
                STX, Handle::kDefaultMaxLength + 1> ();
            static const Operation OpC = { "SetPlayer",
                kRxHeaderC, Params<0> (),
                "Sets the player at the given #index to the given "
                "#dislpay_name.", 0
            };
            if (!expr) return &OpC;
            int32_t player_number;
            char display_name[User::kDefaultMaxDislpayNameLength + 1],
                 handle[Handle::kDefaultMaxLength];
            if (!ExprArgs (expr, kRxHeaderC, Args (args, &player_number,
                                                   display_name, handle)))
                return expr->result;
            if (player_number < 0) {
                return Result (expr, Bin::InvalidArgumentError, Params<1, SI4> ());
            }
            if (player_number > kMaxPlayers) {
                return Result (expr, Bin::InvalidArgumentError, Params<1, SI4> ());
            }
            players_.Grow (player_number);
            player = players_[player_number];
            player->SetDislpayName (display_name);
            player->SetHandle (handle);
            return nullptr;
        }
    }
    return nullptr;
}

const char* DefaultPlayAgainString () {
    static const char play_again[] = "\n| Do you want to play again?"
        "\n| Enter y to continue, or n to quit."
        "\n< \0";
    return play_again;
}

}       //< namespace cards
}       //< namespace kabuki