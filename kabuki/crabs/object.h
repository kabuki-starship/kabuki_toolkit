/* Kabuki Toolkit
    @version 0.x
    @file    ~/kabuki-toolkit/kabuki/crabs/object.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2014-8 Cale McCollough <calemccollough@gmail.com>;
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
#if MAJOR_SEAM > 1 || MAJOR_SEAM == 1 && MINOR_SEAM >= 3
#ifndef HEADER_FOR_CRABS_OBJECT
#define HEADER_FOR_CRABS_OBJECT
// Dependencies:
#include "type.h"
// End dependencies.

namespace _ {

/* An ASCII Object.
    The definition of an ASCII Objects is an object that start with a 8, 16,
    32, or 64-bit word that stores the size of the object in bytes.
*/
template <typename UI>
struct KABUKI AObject {
  uintptr_t* buffer;
};

/* Returns the object size. */
template <typename UI = uint32_t>
UI ObjectSize(const void* object, type_t type) {
  ASSERT(object)
  if (type == 0) return 0;
  if (type <= SI1) return 1;
  if (type <= BOL) return 2;
  if (type <= TMS) return 4;
  if (type <= DBL) return 8;
  if (type <= DEC) return 16;
  if ((type & 0x1F) == UIX) return 32 + (type >> 5);
  if ((type >> 5) == 1) {
  }
  switch (type >> 6) {
    case 0:
      return (UI) * reinterpret_cast<const uint8_t*>(object);
    case 1:
      return (UI) * reinterpret_cast<const uint16_t*>(object);
    case 2:
      return (UI) * reinterpret_cast<const uint32_t*>(object);
    case 3:
      return (UI) * reinterpret_cast<const uint64_t*>(object);
  }
  return 0;
}

/* Aligns the given word to 64-bit word boundary. */
template <typename TextWord4>
inline TextWord4 WordAlign8(TextWord4 value) {
  return value + (((~value) + 1) & (sizeof(TextWord4) - 1));
}

/* Clones the other object. */
template <typename UI = uint32_t>
AObject<UI>* ObjectClone(AObject<UI>* object) {
  ASSERT(object);
  UI* size_ptr = reinterpret_cast<UI*>(object);
  UI size = (*size_ptr) >> kWordBitCount;
  uintptr_t *buffer = new uintptr_t[size], *read = buffer,
            *write = reinterpret_cast<uintptr_t*>(object);
  for (; size > 0; --size) *write++ = *read++;
  return *reinterpret_cast<UI*>(buffer);
}

/* Returns the last byte in the data array. */
template <typename UI>
inline char* ObjectEnd(type_t type, char* object) {
  return object + ObjectSize<UI>(object, type);
}

/* Returns the last byte in the data array. */
template <typename UI, typename TextWord4 = char*>
inline TextWord4* ObjectEnd(TextWord4* object, type_t type) {
  return object + ObjectSize<UI>(object, type);
}

template <typename TextWord4, typename UI = uint, typename SI = int>
inline SI ObjectCountRound(SI count) {
  enum {
    kRoundEpochMask = (sizeof(SI) == 8)
                          ? 7
                          : (sizeof(SI) == 4) ? 3 : (sizeof(SI) == 2) ? 1 : 0,
  };
  SI count_aligned = AlignUpSigned<SI>(count);
}

}  // namespace _ {
#endif  //< #if MAJOR_SEAM > 1 || MAJOR_SEAM == 1 && MINOR_SEAM >= 4
#endif  //< HEADER_FOR_CRABS_OBJECT
