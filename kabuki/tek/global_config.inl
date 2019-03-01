/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /firmware/global_config.inl
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2014-19 (C) Cale Jamison McCollough <<cale@astartup.net>>. 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain 
one at https://mozilla.org/MPL/2.0/. */

#pragma once

#ifndef KABUKI_FEATURES_TEK_GLOBAL_CONFIG_INL
#define KABUKI_FEATURES_TEK_GLOBAL_CONFIG_INL 1
#include "../../script2/global_config.inl"

typedef UI1 offset_t;
typedef UI2 ch_t;

enum {
  // Number of bits to shift to get the UI1 offset.
  kBitToByteShift = sizeof (UI1) * 8,
  // Mask for the bit number, which is UI1.
  kBitNumberMask = 0xff,
};

#define _0_0_0__00 1   //< all
#define SEAM_N 17
#endif  //< #ifndef SCRIPT2_GLOBAL_INLINE_CONFIG
