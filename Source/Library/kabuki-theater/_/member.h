/** The Chinese Room
    @version 0.x
    @file    ~/Member.h
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

#ifndef CHINESEROOM_MEMBER_H
#define CHINESEROOM_MEMBER_H

#include "error.h"

namespace _ {

/** Stores the key/name string, rx_header, tx_header, and optional description
    string.
    @code
    static const Member this_member = { "Key", Rx<1, 2>::Header, Tx<1, 2>::Header,
                                        "Description" };
    static const Member member_device = { "Key", setNumMembers (0), 0,
                                          "Description" };
    @endcode
*/
struct Member {
    const char* key;            //< The member key.
    const uint_t* rx_header,    //< The rx format header. 
        * tx_header;            //< The tx format header.
    const char* description;    //< Optional member description.
};

/** Converts the value to a pointer. */
INLINE uint_t* NumMembers (std::uintptr_t value) {
    return reinterpret_cast<uint_t*> (value);
}

/** Creates a Read-only-memory Member for a member without a description. */
template<const char* key>
INLINE const Member* DeviceMember () {
    static const Member m = { key, 0, 0, 0 };
    return &m;
}

/** Creates a Read-only-memory Member for a member without a description. */
template<const char* key, byte num_members, const uint_t* rx_header,
         const uint_t* tx_header>
INLINE const Member* DeviceMember () {
    static const Member m = { key, rx_header, tx_header, 0 };
    return &m;
}

/** Creates a static const Member in ROM.
    @code
    const Member* m = createMember<"memberName", 1, TxHeader<FLT, TMU>,
        "Description.">
    @endcode
*/
template<const char* kKey, const uint_t* kHeaderIn, const char* kHeaderOut,
         const char* kDescription>
INLINE const Member* DeviceMember () {
    static Member m = { kKey, kHeaderIn, kHeaderOut, kDescription };
    return &m;
}

/** Creates a Read-only-memory Member for a Device. */
template<const char* key, byte num_members, const uint_t* tx_header,
         const char* description>
INLINE const Member* DeviceMember () {
    static const Member m = { key, ConvertNumMembers (num_members), tx_header,
        description };
    return &m;
}

/** Creates a Read-only-memory Member for a Device. */
template<const char* key, byte num_members, const char* description>
INLINE const Member* MemberDevice () {
    static const Member m = { key, ConvertNumMembers (num_members), 0,
        description };
    return &m;
}

/** Converts the given value to a pointer. */
INLINE const uint_t* FirstMember (uint_t value) {
    return reinterpret_cast<uint_t*>(value);
}

/** Returns the number of members an Device has. */
INLINE uintptr_t Index (const void* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

/** Returns the number of members a Device has. */
INLINE uintptr_t GetNumMembers (const Member* m) {
    return Index (m->rx_header);
}

/** Error flag member pointers for throwing Terminal io errors. */
INLINE const Member* ReadError () {
    //return DeviceMember<"Read"> ();
    static const Member error = { "Read",
        0,
        0,
        0
    };
    return &error;
}

/** Error flag member pointers for throwing Terminal io errors. */
INLINE const Member* WriteError () {
    //return DeviceMember<"Write"> ();
    static const Member error = { "Write",
        0,
        0,
        0
    };
    return &error;
}

/** Error flag member pointers for throwing Terminal io errors. */
INLINE const Member* DeviceStackOverflowError () {
    //return DeviceMember<"Device stack overflow"> ();
    static const Member error = { "Device stack overflow",
        0,
        0,
        0
    };
    return &error;
}

/** An error flag for an invalid member index. */
INLINE const Member* InvalidMember () {
    //return DeviceMember<"Invalid member index"> ();
    static const Member error = { "Invalid member index",
        0,
        0,
        0
    };
    return &error;
}

/** Prints the given Member to the std::out */
INLINE void Print (const Member* m) {
    if (m == nullptr)
        return;

    const uint_t* tx_header = m->tx_header;

    if (Index (tx_header) < 256) {
        // Print Member Device
        std::cout << "\n| NumMembers:  " << GetNumMembers (m)
            << "\n| Description: " << m->description << '\n';
    }

    std::cout << "| Name:          " << m->key;
    PrintEsc (m->rx_header);
    std::cout << '\n';
    PrintEsc (m->tx_header);
    std::cout << "\n| Description: " << m->description << '\n';
}

}   //< namespace _

#endif  //< CHINESEROOM_MEMBER_H
