/** The Chinese Room
    @version 0.x
    @file    ~/mirror.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <calemccollough.github.io>
                            All right reserved (R).
             Licensed under the Apache License, Version 2.0 (the "License"); 
             you may not use this file except in compliance with the License. 
             You may obtain a copy of the License at
                        http://www.apache.org/licenses/LICENSE-2.0
             Unless required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS,
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
             implied. See the License for the specific language governing 
             permissions and limitations under the License.
*/

#ifndef CHINESEROOM_MIRROR_H
#define CHINESEROOM_MIRROR_H

#include "portal.h"
#include "uniprinter.h"

namespace _ {

class Mirror: public Portal
{
    public:

    Mirror ():
        up (nullptr)
    {

    }

    virtual void Prime () {

    }

    virtual uint_t Length () {
        return UniprinterLength (UniprinterRx (io));
    }

    virtual void Feed (byte b) {

    }

    virtual byte Pull () {
        return 0;
    }

    private:

    Uniprinter* io;     //< The uniprinter we're writing to.
};

ticket_t Read (Mirror* io, const uint_t* header, void** args) {

    return 0;
}

ticket_t Write (Mirror* io, const uint_t* header, void** args) {

    return 0;
}

}       //< namespace _
#endif  //< CHINESEROOM_MIRROR_H
                                                                       