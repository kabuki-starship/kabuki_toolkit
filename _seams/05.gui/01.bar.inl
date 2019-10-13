/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.git
@file    /gui/tests/01_bar.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2019 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM == GUI_BAR
#include <script2/module_debug.inl>
#else
#include <script2/module_release.inl>
#endif

using namespace _;

namespace gui {
inline const CHA* Bar(CHA* seam_log, CHA* seam_end, const CHA* args) {
#if SEAM >= KABUKI_TOOLKIT_PRO_0
  A_TEST_BEGIN;

#endif
  return 0;
}
}  // namespace gui
