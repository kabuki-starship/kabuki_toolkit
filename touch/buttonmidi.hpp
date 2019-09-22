/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.git
@file    /touch/buttonmidi.hpp
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <module_config.h>
#if SEAM >= KABUKI_TOOLKIT_AV_1
#ifndef KABUKI_TOOLKIT_AV_MIDIBUTTON
#define KABUKI_TOOLKIT_AV_MIDIBUTTON

#include "button.hpp"
#include "controlmidi.hpp"

namespace _ {

class LIB_MEMBER ControlMidi;

/* A button that triggers a MIDIEvent. */
class LIB_MEMBER TButtonMIDI : public ControlMidi, public Button {
 public:
  /* Constructor. */
  TButtonMIDI(AString newLabel = "", SI4 cc = 0, SI4 channel = 0, SI4 value = 0,
             SI4 min_value = 0, SI4 max_value = 127, SI4 word_size = 7,
             SI4 action = Button::Momentary, SI4 newStepSize = 0,
             FP8 double_press_ticks = Button::kDefaultDoublePressTicks)
    : Button (new_action, step_size, double_press_ticks),
    ControlMidi (label, cc, channel, value, min_value, max_value, word_size,
      Parameter<SI4>::TButtonMIDI) {}

  /* Virtual destructor. */
  virtual ~TButtonMIDI() {}

  /* Toggles the state of the Button if type is latching. */
  void Toggle() override {
    if (value () != max_value_ ())
      SetValue (max_value_ ());
    else
      SetValue (MinValue ());
  }

  /* Gets the header for toStringRow (). */
  void PrintHeaderString() const override {
    o << ControlMidi::HeaderString (); 
    if (type () == Parameter<SI4>::ControlMidi) return o;
    return o << "  Action  |Step |";
  }

  /* Prints a column of the values without the labels. */
  void PrintRow() const override {
    return o << PrintStringRow (0)
             << Centered (actionString (), 10) 
             << "|" << Centered (StepSize (), 5) << "|";
  }

 private:
  ControlMidi* control_;  //< This Button's ControlMidi.

};  //< class MidiButton
}  // namespace _
#endif  //< KABUKI_TOOLKIT_AV_MIDIBUTTON
#endif  //< #if SEAM >= KABUKI_TOOLKIT_AV_1
