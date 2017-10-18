/** Kabuki Starship
    @file    /.../Source-Impl/_Id/User.cpp
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <https://calemccollough.github.io>

                            All right reserved (R).

        Licensed under the Apache License, Version 2.0 (the "License"); you may
        not use this file except in compliance with the License. You may obtain
        a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
*/

#include <_Id/User.h>

namespace _Id {

User::User (const string& aName, const string& aPassword)
:   name (aName),
    password (aPassword)
{
    //activeAccounts = new Kabuki Starship.Game.Account.List ();
}

Handle& User::getUsername () { return name; }

Password& User::getPassword ()
{
    return password;
}

bool User::verify (const string& aUsername, const string& aUser)
{
    //return isValidUsername (aUsername);
    return false;
}

bool User::equals (const User& u)
{
    return (name.equals (u.name) && password.equals (u.password));
}

bool User::equals (const string& aName)
{
    return name.equals (aName);
}

void User::print (Terminal& io)
{
    slot.prints ("User Name: ");
    name.print (slot);
    slot.prints (" Password: ");
    password.print (slot);
}

}   //  _Id
