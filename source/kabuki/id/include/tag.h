/** Kabuki Theater
    @file    /.../Source/_id/Person.h
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
 
#pragma once

#include <KabukiTheater-Config.h>

namespace _id {

class ID_API ITag_i
{
    public:

    virtual int getUID () = 0;
    /*< Gets the Unique identifier number. */

    virtual string setUID (int value) = 0;
    /*< Sets the Unique identifier number. */

    virtual string getName () = 0;
    /*< Gets the ID name. */

    virtual string setName (const string& name) = 0;
    /*< Sets the ID name. */
    
    virtual void print (Terminal& io) = 0;
    /*< Prints this object to a terminal. */
};
}   //< _id
