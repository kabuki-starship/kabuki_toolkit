/** The Chinese Room
    @version 0.x
    @file    ~/types.h
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

#ifndef CHINESEROOM_TYPES_H
#define CHINESEROOM_TYPES_H

#include "utils.h"

namespace _ {

/** List of the 32 data types.
    This has been mimicked in order to match the ASCII C0 codes as closely 
    as sanely possible. Many of the codes just don't make sense as types, but 
    the codes were picked for the specific purpose that they are not human 
    readable, with the exception of HT, VT, CR, and LF. */
typedef enum {
    NIL   = 0,  //< 0.  NIL/null/void type.
    SOH   = 1,  //< 1.  An address to an I2P device.
    STX   = 2,  //< 2.  A UTF-8/ASCII string.
    SI1   = 3,  //< 3.  An 8-bit signed integer.
    UI1   = 4,  //< 4.  An 8-bit unsigned integer.
    BOL   = 5,  //< 5.  An 8-bit non-zero asserted boolean variable.
    SI2   = 6,  //< 6.  A 16-bit signed integer.
    UI2   = 7,  //< 7.  A 16-bit unsigned integer.
    HLF   = 8,  //< 8.  A 16-bit floating-point number.
    SI4   = 9,  //< 9.  A 32-bit signed integer.
    UI4   = 10, //< 10. A 32-bit unsigned integer.
    FLT   = 11, //< 11. A 32-bit floating-point number.
    TMS   = 12, //< 12. A 32-bit second since epoch timestamp.
    TMU   = 13, //< 13. A 64-bit microsecond since epoch timestamp.
    SI8   = 14, //< 14. A 64-bit signed integer.
    UI8   = 15, //< 15. A 64-bit unsigned integer.
    DBL   = 16, //< 16. A 64-bit floating-point number.
    SV2   = 17, //< 17. A 16-bit signed varint.
    UV2   = 18, //< 20. A 16-bit unsigned varint.
    SV4   = 19, //< 18. A 32-bit signed varint.
    UV4   = 20, //< 21. A 32-bit unsigned varint.
    SV8   = 21, //< 19. A 64-bit signed varint.
    UV8   = 22, //< 22. A 64-bit unsigned varint.
    AR1   = 23, //< 23. An array of up to 2^8-1 like primitive types 3-16.
    AR2   = 24, //< 24. An array of up to 2^16-1 like primitive types 3-16.
    AR4   = 25, //< 25. An array of up to 2^32-1 like primitive types 3-16.
    AR8   = 26, //< 26. An array of up to 2^32-1 like primitive types 3-16.
    ESC   = 27, //< 27. An atomic escape sequence of I2P procedure calls.
    BK8   = 28, //< 28. A book with up to 2^31-2 members and 2^64-1 bytes data.
    BK4   = 29, //< 29. A book with up to 2^15-2 members and 2^32-1 bytes data.
    BK2   = 30, //< 30. A book with up to 2^7-2 members and 2^16-1 bytes data.
    US    = 31, //< 31. A unit separator for breaking files and data into 
                //<     transmission blocks.
} TType;

enum {
    kInvalidType = 32,  //< The starting index of invalid types.
};

/** Gets the width in bytes (1-8) of the given type. */
INLINE uint_t SizeOf (uint_t type) {
    static const int8_t kWidths[] =
    {
        0,      //< NIL: 0 
        0,      //< SOH: 1 
        0,      //< STX: 2 
        1,      //< SI1: 3 
        1,      //< UI1: 4 
        1,      //< BOL: 5 
        2,      //< SI2: 6 
        2,      //< UI2: 7 
        2,      //< HLF: 8 
        4,      //< SI4: 9 
        4,      //< UI4: 10
        4,      //< FLT: 11
        4,      //< TMS: 12
        8,      //< TMU: 13
        8,      //< SI8: 14
        8,      //< UI8: 15
        8,      //< DBL: 16
        3,      //< SV2: 17
        3,      //< UV2: 18
        9,      //< SV4: 19
        5,      //< UV4: 20
        9,      //< SV8: 21
        9,      //< UV8: 22
        0,      //< GS1: 23
        0,      //< GR2: 24
        0,      //< GR4: 25
        0,      //< GR8: 26
        0,      //< ESC: 27
        0,      //< FS:  28
        0,      //< BK2: 29
        0,      //< BK4: 30
        0,      //< BK8: 31
    };
    if (type >= 32)
        return 0;
    return kWidths[type];
}

/** Aligns the given pointer to a word-aligned boundary. */
INLINE const byte* TypeAlignments () {
    static const byte kWidths[] =
    {
        0,      //< NIL: 0 
        0,      //< SOH: 1 
        0,      //< STX: 2 
        0,      //< SI1: 3 
        0,      //< UI1: 4 
        0,      //< BOL: 5 
        2,      //< SI2: 6 
        2,      //< UI2: 7 
        2,      //< HLF: 8 
        4,      //< SI4: 9 
        4,      //< UI4: 10
        4,      //< FLT: 11
        4,      //< TMS: 12
        8,      //< TMU: 13
        8,      //< SI8: 14
        8,      //< UI8: 15
        8,      //< DBL: 16
        2,      //< SV2: 17
        2,      //< UV2: 18
        4,      //< SV4: 19
        4,      //< UV4: 20
        8,      //< SV8: 21
        8,      //< UV8: 22
        0,      //< AR1: 23
        2,      //< AR2: 24
        4,      //< AR4: 25
        8,      //< AR8: 26
        8,      //< ESC: 27
        8,      //< BK8: 28
        8,      //< BK4: 29
        8,      //< BK2: 30
        8,      //< US:  31
    };
    return kWidths;
}

/** Aligns the given pointer to a word-aligned boundary. */
INLINE uintptr_t TypeAlign2 (byte* ptr) {
    // Mask off lower bit and add it to the ptr.
    uintptr_t value = reinterpret_cast<uintptr_t> (ptr);
    return value & 0x1;
}

/** Aligns the given pointer to a word-aligned boundary. */
INLINE uintptr_t TypeAlign4 (byte* ptr) {
    return WordAlignOffset<int> (ptr);
}

/** Aligns the given pointer to a word-aligned boundary. */
INLINE uintptr_t TypeAlign8 (byte* ptr) {
    return WordAlignOffset<long> (ptr);
}

/** Aligns the given pointer to a word-aligned boundary. */
INLINE uintptr_t TypeAlign (byte* ptr, byte type) {
    if (type >= 32)     return 0;
    byte alignment = TypeAlignments ()[type];
    if (alignment <= 1) return 0;
    uintptr_t offset;
    if (alignment == 4) return TypeAlign4 (ptr);
    if (alignment == 8) return TypeAlign8 (ptr);
    // else alignment == 2
    // Mask off lower bit and add it to the ptr.
    uintptr_t value = reinterpret_cast<uintptr_t> (ptr);
    offset = value & 0x1;
    return offset;
}

/** Aligns the given pointer to a word-aligned boundary. */
INLINE uintptr_t TypeAlign (byte* ptr, uint_t type) {
    if (type >= 32)     return 0;
    byte alignment = TypeAlignments ()[type];
    if (alignment <= 1) return 0;
    uintptr_t offset;
    if (alignment == 4) return TypeAlign4 (ptr);
    if (alignment == 8) return TypeAlign8 (ptr);
    // else alignment == 2
    // Mask off lower bit and add it to the ptr.
    uintptr_t value = reinterpret_cast<uintptr_t> (ptr);
    offset = value & 0x1;
    return offset;
}

/** Returns true if the type is a valid list type. */
INLINE bool TypeIsValid (uint_t type) {
    return type > 31 ? false : true;
}

/** Returns a pointer to an array of pointers to the type names.*/
INLINE const char** TypeStrings () {
    static const char* kNames[] = {
        "NIL",
        "SOH",
        "STX",
        "SI1",
        "UI1",
        "BOL",
        "SI2",
        "UI2",
        "HLF",
        "SI4",
        "UI4",
        "FLT",
        "TMS",
        "TMU",
        "SI8",
        "UI8",
        "DBL",
        "SV2",
        "UV2",
        "SV4",
        "UV4",
        "SV8",
        "UV8",
        "AR1",
        "AR2",
        "AR4",
        "AR8",
        "ESC",
        "BK8",
        "BK4",
        "BK2",
        "US",
        "Invalid"
    };
    return kNames;
}

/** Returns true if the TypeName is one of the ErrorStrings. */
INLINE bool TypeIsValid (const char* type_name) {
    if (type_name < TypeStrings ()[0] || type_name > TypeStrings ()[BK8])
        return false;
    return true;
}

/** Returns the name of the given type. */
INLINE const char* TypeString (uint_t type) {
    if (type >= kInvalidType)
        return "Invalid";
    return TypeStrings ()[type];
}

/** Checks to see if the given byte is a delimiter. */
INLINE bool CheckDelimiter (char const c) {
    if (c == 0   ) return false;
    if (c == ' ' ) return false;
    if (c == '\n') return false;
    if (c == '\t') return false;
    return true;
}

/** Checks the last char of the token to check if it is a specified char. */
template<char c>
INLINE bool CheckLastLetter (uint16_t const token) {
    if (c != (char)token) return true;
    return CheckDelimiter (token >> 8);
}

/** Checks the last two char(s) of the token to check if it is a specified char. */
template<char LetterTwo, char LetterThree>
INLINE bool CheckLastLetters (uint32_t const Token) {
    char check = Token >> 8;
    if (LetterTwo != check) return true;

    check = Token >> 16;
    if (LetterThree != check) return true;

    check = Token >> 24;
    return CheckDelimiter (Token >> 8);
}

/** Returns the type from the given index.
    @warning Untested. */
INLINE byte ReadType (const char* s) {
    uint32_t token = * ((uint32_t*)s);

    byte index = (byte)token;

    switch (index)
    {
        case 'A': {
            if ((byte)(token >> 8) != 'R')
                return 0xff;    //< There are only AR1, AR2, AR4, and AR8
            switch (index = (byte)(token >> 16)) {
                case '1': return CheckDelimiter (token >> 24) ? 0xff : AR1;
                case '2': return CheckDelimiter (token >> 24) ? 0xff : AR2;
                case '4': return CheckDelimiter (token >> 24) ? 0xff : AR4;
                case '8': return CheckDelimiter (token >> 24) ? 0xff : AR8;
                default: return 0xff;
            }
        }
        case 'B': switch (index = (byte) (token >> 8))
        {
            case 'K': switch (index = (byte) (token >> 16))
            {
                case '2': return CheckDelimiter (token >> 24) ? 0xff : BK2;
                case '4': return CheckDelimiter (token >> 24) ? 0xff : BK4;
                case '8': return CheckDelimiter (token >> 24) ? 0xff : BK8;
                default: return 0xff;
            }
            case 'O': return CheckLastLetter<'L'> (token >> 16) ? 0xff : BOL;
            default: return 0xff;
        }
        case 'D': return CheckLastLetters<'B', 'L'> (token >> 16) ? 0xff : DBL;
        case 'E': return CheckLastLetters<'S', 'C'> (token >> 16) ? 0xff : ESC;
        case 'F': return CheckLastLetters<'L', 'T'> (token >> 16) ? 0xff : FLT;
        case 'G': return 0xff;
        case 'H': return CheckLastLetters<'L', 'F'> (token >> 16) ? 0xff : HLF;
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M': return 0xff;
        case 'N': return CheckLastLetters<'I', 'L'> (token >> 16) ? 0xff : NIL;
        case 'O':
        case 'P':
        case 'Q':
        case 'R': return 0xff;
        case 'S': switch (index = (byte) (token >> 8))
        {
            case 'I': switch (index = (byte) (token >> 16))
            {
                case '1': return CheckDelimiter (token >> 24) ? 0xff : SI1;
                case '2': return CheckDelimiter (token >> 24) ? 0xff : SI2;
                case '4': return CheckDelimiter (token >> 24) ? 0xff : SI4;
                case '8': return CheckDelimiter (token >> 24) ? 0xff : SI8;
                default: return 0xff;
            }
            case 'O': switch (index = (byte) (token >> 16))
            {
                case 'H': return CheckDelimiter (token >> 24) ? 0xff : SOH;
                default: return 0xff;
            }
            case 'V': switch (index = (byte) (token >> 16))
            {
                case '4': return CheckDelimiter (token >> 24) ? 0xff : SV4;
                case '8': return CheckDelimiter (token >> 24) ? 0xff : SV8;
                default: return 0xff;
            }
            default: break;
        }
        case 'T': switch (index = (token >> 8))
        {
            case 'M': switch (index = (token >> 16))
            {
                case 'E': return CheckDelimiter (token >> 24) ? 0xff : TMS;
                case 'U': return CheckDelimiter (token >> 24) ? 0xff : TMU;
                default: return 0xff;
            }
            default: return 0xff;
        }
        case 'U': switch (index = (token >> 8))
        {
            case 'S': return CheckDelimiter (token >> 16) ? 0xff : US;
            case 'I': switch (index = (byte) (token >> 16))
            {
                case '1': return CheckDelimiter (token >> 24) ? 0xff : UI1;
                case '2': return CheckDelimiter (token >> 24) ? 0xff : UI2;
                case '4': return CheckDelimiter (token >> 24) ? 0xff : UI4;
                case '8': return CheckDelimiter (token >> 24) ? 0xff : UI8;
                default: return 0xff;
            }
            case 'V': switch (index = (byte) (token >> 16))
            {
                case '4': return CheckDelimiter (token >> 24) ? 0xff : UV4;
                case '8': return CheckDelimiter (token >> 24) ? 0xff : UV8;
                default: return 0xff;
            }
            default: return 0xff;
        }
    }
    return 0xff;
}

/** Masks off the lower 5-LSb to get the type. */
INLINE byte MaskType (byte value) {
    return value & 0x1f;
}

/** Returns true if this type has a buffer. */
INLINE bool TypeHasLength (uint_t type) {
    if (type == STX)
        return true;
    if (type >= AR1 && type <= AR8)
        return true;
    if (type == ESC)
        return false;
    return false;
}

/*< Returns true if the given type is an Array type. */
INLINE bool TypeIsArray (uint_t type) {
    return (type >= AR1) && (type <= AR8);
}

/*< Returns true if the given type is a Book type. */
INLINE bool TypeIsBook (uint_t type) {
    return (type >= BK8) && (type <= BK2);
}

/** Returns true if this type has a buffer. */
INLINE bool TypeIsHierarchical (uint_t type) {
    return type > ESC;
}


/*< Converts from a 2's complement integer to a signed varint.
    @param value A 2's complement integer.
    @return An signed varint.
    A signed varint is an uncomplemented signed integer with the sign in the 
    LSb. To convert a negative 2's complement value to positive invert the bits 
    and add one.
*/
template<typename T>
INLINE T PackSignedVarint (T value) {
    T sign_bit = value >> ((sizeof (T) * 8 - 1));   //< Extract the sign bit.
    if (sign_bit != 0) {
        T uncomplemented = (~value) + 1;
        return sign_bit | (uncomplemented << 1);
    }
    // Else don't uncomplement.
    return value << 1;
}

/*< Converts from a signed varint to a 2's complement signed integer.
    @param  A signed integer casted as an unsigned integer.
    @return Returns a standard signed integer cased as unsigned.
    A varint is an uncomplemented signed integer with the sign in the LSb. */
template<typename T>
INLINE T UnpackSignedVarint (T value) {
    T sign_bit = value << (sizeof (T) * 8 - 1);
    value = value >> 1;
    if (sign_bit != 0) {
        value = ~(value - 1);
        return value;
    }
    return value;
}

}       //< namespace _
#endif  //< CHINESEROOM_TYPES_H
