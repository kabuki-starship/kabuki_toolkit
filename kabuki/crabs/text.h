
/* Kabuki Toolkit
  @version 0.x
  @file    ~/kabuki-toolkit/kabuki/crabs/text.h
  @author  Cale McCollough <cale.mccollough@gmail.com>
  @license Copyright (C) 2014-2017 Cale McCollough <calemccollough@gmail.com>;
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
#if MAJOR_SEAM > 1 || MAJOR_SEAM == 1 && MINOR_SEAM >= 2
#ifndef HEADER_FOR_CRABS_TEXT
#define HEADER_FOR_CRABS_TEXT
// Dependencies:
#include "config.h"
// End dependencies.

namespace _ {

/* Creates/Gets a static buffer of the specified size. */
template <size_t kBufferSize = kBufferSizeDefault>
inline char* Buffer() {
  enum {
    kBufferSizeWords =
        (kBufferSize / sizeof(uintptr_t)) + kBufferSize % sizeof(uintptr_t) ? 1
                                                                            : 0
  };
  static uintptr_t buffer[kBufferSizeWords];
  return reinterpret_cast<char*>(buffer);
}

/* String (STR) and Address (ADR) Text (TKN) utilities
    @ingroup Text

    A String is nil-terminated in the SCRIPT Protocol and is double-quote-
    terminated in Interprocess LISP. In Interprocess LISP we will end up
    running all the bytes through the Expression Interpreter, thus need these
    utilities to work with nil-terminated strings and whitespace delimited
    tokens and not Interprocess LISP.
*/

enum {
  kMaxDigitsFloat = 3 + FLT_MANT_DIG - FLT_MIN_EXP,
  kMaxDigitsDouble = 3 + DBL_MANT_DIG - DBL_MIN_EXP,
};

/* Empty string.
    @warning This will generate a duplicate copy of the */
template <typename Char>
inline const char* Empty() {
  static const Char kString[] = {'\0'};
  return kString;
}

/* New line string. */
template <typename Char>
inline const char* NewLine() {
  static const Char kString[] = {'\n'};
  return kString;
}

/* Error header string. */
template <typename Char>
inline const char* ErrorHeader() {
  static const Char kString[] = {'\n', 'E', 'r', 'r', 'o', 'r', ':', '\0'};
  return kString;
}

/* Checks if the given character is whitespace.
 */
inline bool IsWhitespace(char character) { return character <= ' '; }

/* Converts the given value to a printable char if it's non-printable. */
inline char Char(char value) {
  if (value < 32 || value == 127) return ' ';
  return value;
}

/* Scrolls over to the next double quote mark.
    @warning This function is only safe to use on ROM strings with a nil-term
             char. */
KABUKI const char* TextEnd(const char* text, char delimiter = 0);

/* Gets the length of the given char.
    @return  Returns -1 if the text char is nil.
    @warning This function is only safe to use on ROM strings with a nil-term
             char. */
template <typename UI = uint, typename char_t = char>
KABUKI UI TextLength(const char_t* text, char_t delimiter = 0) {
  ASSERT(text)
  UI count = 0;
  char_t c = *text;
  while (c > delimiter) {
    UI upper_bounds = 0;           //< Faster to make from instructions then
    upper_bounds = ~upper_bounds;  //< load from ROM.
    if (count == upper_bounds) return 0;
    ++count;
    c = *(++text);
  }
  return count;
}

/* Gets the length of the given char.
    @return  Returns -1 if the text char is nil.
    @warning This function is only safe to use on ROM strings with a nil-term
             char. */
KABUKI int TextLength(const char* text, char delimiter = 0);

/* Gets the length of the given char.
    @return  Returns -1 if the text char is nil.
    @warning This function is only safe to use on ROM strings with a nil-term
             char. */
KABUKI int TextLength(const char16_t* text, char16_t delimiter = 0);

/* Clones the given string with given NON-ZERO delimiter.
    @param  A nil-terminated string in ROM.
    @return Returns a new copy you must delete. */
KABUKI char* TextClone(const char* text, char delimiter = 0);

/* Returns a pointer to the char at the end of the line. */
KABUKI const char* TextLineEnd(const char* text, int num_columns,
                               char delimiter = 0);

/* Returns a pointer to the char at the end of the row. */
KABUKI const char* TextLineEnd(const char* text, const char* text_end,
                               int num_columns, char delimiter = 0);

/* Returns the pointer to the next char in the char that is not an ASCII
number.
    @return A pointer to the next non-number in the text char. */
KABUKI const char* TextNextNonNumber(const char* text, const char* text_end,
                                     char delimiter = 0);

/* Returns the pointer to the next char in the char that is not an ASCII
    number.
    @return A pointer to the next non-number in the text char. */
KABUKI const char* TextSkipNumbers(const char* text, char delimiter = 0);

/* Skips the leading zeros of a number if there are any. */
KABUKI const char* TextSkipChar(const char* text, char skip_char,
                                char delimiter = 0);

/* Skips all the spaces at the start of the char. */
KABUKI const char* TextSkipSpaces(const char* text);

/* Skips all the spaces at the start of the char.
    @param  begin Beginning address of the read buffer.
    @param  end   The end address of the input buffer.
    @return A pointer to the end of the text read or if no text read. */
KABUKI const char* TextSkipSpaces(const char* text, const char* text_end);

/* Compares the source and query char as nil-terminated strings. */
KABUKI const char* TextEquals(const char* text_a, const char* text_b,
                              char delimiter = 0);

/* Compares the source and query char as nil-terminated strings. */
KABUKI const char* TextEquals(const char* text, const char* text_end,
                              const char* query, char delimiter = 0);

/* Searches the given char for the given char.
    @param  text      The char to search.
    @param  query      The char to search for.
    @param  delimiter The delimiter for the text, Example: '\"'
    @return Returns nil if the parsing failed and a pointer to the first char
            after the end of the text upon success. */
KABUKI const char* TextFind(const char* text, const char* query,
                            char delimiter = 0);

}       //< namespace _
#endif  //< #if MAJOR_SEAM > 1 || MAJOR_SEAM == 1 && MINOR_SEAM >= 3
#endif  //< HEADER_FOR_CRABS_TEXT
