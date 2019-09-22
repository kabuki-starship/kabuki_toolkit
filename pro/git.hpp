/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.git
@file    /pro/t_git.hpp
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <module_config.h>
#if SEAM >= KABUKI_PRO_1
#ifndef KABUKI_PRO_GIT
#define KABUKI_PRO_GIT 1

namespace _ {

/* Script2 wrapper class for scanning git console commands. */
class Git : public Operand {
 public:
  /* Constructs nothing. */
  Git();

  template<typename Printer>
  Printer& Print (Printer& o) {
    return o << "\nGit:";
  }

  /* Script2 operations. */
  virtual const Op* Star(wchar_t index, Expr* expr) {
    void* args[1];
    enum { kSize = 254 };
    CH1 buffer[kSize + 1];
    switch (index) {
    case '?': {
      static const Op kThis = { "Sloth", OpFirst (' '), OpLast (' '), "git",
                               '}',     ';',          ' ',         false,
                               nullptr, nullptr,      nullptr };
      return &kThis;
    }
    case ' ': {
      static const Op kClone = {
          "clone", Params<1, TKN, 255> (),
          0,       "Push Operation that occurs upon updating the toolkit.",
          '}',     ';',
          ' ',     false,
          0,       0,
          0 };
      if (!expr) return &kClone;
      Print (buffer, buffer + 255, "git clone ");
      if (!ExprArgs (expr, kClone, Args (args, &buffer[10]))) 
        return expr->result;
      system (&buffer[9]);
      return 0;
    }
    }
    return nullptr;
  }
};
}  // namespace _
#endif  //< KABUKI_PRO_GIT
#endif  //< #if SEAM >= KABUKI_PRO_1
