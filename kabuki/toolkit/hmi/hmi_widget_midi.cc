/* Kabuki Toolkit
    @file    ~/source/hmi/hmi_midi_widget.cc
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
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

#include <stdafx.h>
#if MAJOR_SEAM > 2 || MAJOR_SEAM == 2 && MINOR_SEAM >= 2
#if MAJOR_SEAM == 2 && MINOR_SEAM == 2
#define PRINTF(format, ...) printf(format, __VA_ARGS__);
#define PRINT_PAUSE(message)   \
  printf("\n\n%s\n", message); \
  system("PAUSE");
#else
#define PRINTF(x, ...)
#define PRINT_PAUSE(message)
#endif

#include "midi_widget.h"

namespace _ {

const Time WidgetMidi::double_press_time_min(1);
const Time WidgetMidi::double_press_time_max(1000);

WidgetMidi::WidgetMidi(byte commonChannel, byte keyboardChannel,
                       byte drumsChannel)
    : commonChannel(commonChannel),
      keyboardChannel(keyboardChannel),
      drumsChannel(drumsChannel),
      doublePressTime(500) {
  // Nothing to do here yet.
}

WidgetMidi::WidgetMidi(const WidgetMidi& o)
    : commonChannel(o.commonChannel),
      keyboardChannel(o.keyboardChannel),
      drumsChannel(o.drumsChannel) {
  // Nothing to do here yet.
}

WidgetMidi::~WidgetMidi() {
  // Nothing to do here yet.
}

byte WidgetMidi::SetCommonChannel() { return commonChannel; }

void WidgetMidi::SetCommonChannel(byte c) {
  if (c == 0)
    commonChannel = 1;
  else if (c >= 16)
    commonChannel = 16;
  else
    commonChannel = c;
}

byte WidgetMidi::GetKeyboardChannel() { return keyboardChannel; }

void WidgetMidi::SetKeyboardChannel(byte thisChannel) {
  if (thisChannel == 0)
    keyboardChannel = 1;
  else if (thisChannel >= 16)
    keyboardChannel = 16;
  else
    keyboardChannel = thisChannel;
}

byte WidgetMidi::drumsChannel() { return drumsChannel; }

void WidgetMidi::SetDrumsChannel(byte thisChannel) {
  if (thisChannel == 0)
    drumsChannel = 1;
  else if (thisChannel >= 16)
    drumsChannel = 16;
  else
    drumsChannel = thisChannel;
}

Time WidgetMidi::GetDoublePressTime() { return doublePressTime; }

int WidgetMidi::SetDoublePressTime(timestamp_t newTime) {
  if (newTime < minDoubleClickTime) return -1;

  if (newTime > maxDoubleClickTime) return 1;

  doublePressTime = newTime;
  return 0;
}

void WidgetMidi::print() { printf("WidgetMidi:\n"); }

}       //< namespace _
#endif  //< #if MAJOR_SEAM > 2 || MAJOR_SEAM == 2 && MINOR_SEAM >= 2
