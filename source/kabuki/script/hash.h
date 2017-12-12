/** kabuki::script
    @version 0.x
    @file    ~/source/kabuki/script/text.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <calemccollough@gmail.com>;
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

#pragma once
#include <stdafx.h>

#ifndef SCRIPT_HASH_H
#define SCRIPT_HASH_H

#include "config.h"

namespace _ {

//hash16_t Hash16UI2 (uint16_t value, hash16_t hash);


//hash16_t Hash16UI4 (uint32_t value, hash16_t hash);


//hash16_t Hash16UI8 (uint64_t value, hash16_t hash);

/** Hashes a single byte. */
inline hash16_t Hash16 (char c, hash16_t hash) {
    //PrintHex (c);
    hash16_t cprime = c * kLargest16BitPrime;
    return cprime + hash;
}

/** Hashes a single byte. */
inline hash32_t Hash32 (char c, hash32_t hash) {
    hash32_t cprime = c * kLargest32BitPrime;
    return cprime + hash;
}

/** Hashes a single byte. */
inline hash64_t Hash64 (char c, hash64_t hash) {
    hash64_t cprime = c * kLargest64BitPrime;
    return cprime + hash;
}

/** Hashes the given char using the primeHash function. */
KABUKI hash16_t Hash16 (const char* string, hash16_t hash = kLargest16BitPrime);

/** Hashes the given char using the primeHash function. */
KABUKI hash16_t Hash32 (const char* string, hash32_t hash = kLargest32BitPrime);

/** Hashes the given char using the primeHash function. */
KABUKI hash64_t Hash64 (const char* string, hash64_t hash = kLargest64BitPrime);

}       //< namespace _
#endif  //< SCRIPT_HASH_H