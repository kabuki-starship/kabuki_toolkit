/** Kabuki Starship
    @file    /.../Source/_Theater/MIDI/Message.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <https://calemccollough.github.io>

                            All right reserved  (R).

        Licensed under the Apache License, Version 2.0  (the "License"); you may
        not use this file except in compliance with the License. You may obtain
        a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
*/

#pragma once

namespace _midi {

#include <KabukiTheater-Config.h>
    
class Device;

struct HMIDIIn
{
    char A;
};

struct MIDIHDR
{
    char A;
};

class InputHeader
/** Encapsulates the MIDIHDR struct for MIDI input in Win. */
{
    public:

    InputHeader  (HMIDIIn devHandle, byte* buffer, uint32_t length, bool& errorFlag);
	/*< Simple constructor.
		@param devHandle A handle to the MIDI input device.
		@param buffer    The buffer.
        @param length    The length of the buffer.
        @param errorFlag This is a variable that the user passes into the contstructor
            that is set true if there is an error createing */
    
    ~InputHeader ();
    /*< Destructor. */

    bool addSysExBuffer ();
    /*< Add a buffer for receiving SysEx messages. */

    private:

    HMIDIIn deviceHandle;   //< A handle to the MIDIIN device this message will be processed by.
    MIDIHDR midiHeader;     //< The MIDI header for this message.
};

/** Thread safe queue for storing MIDI::Message::InputHeader objects. */
class InputHeaderQueue
{
    public:

    InputHeaderQueue ();
    ~InputHeaderQueue ();

    /** Enqueues a header. */
    void addHeader  (InputHeader *header);

    /** Dequeues a haeder. */
    void removeHeader ();

    /** Dumps the Queue. */
    void removeAll ();

    /** Gets true if the Queue is empty. */
    bool isEmpty ();

    private:

    InputHeader *queue;                     //< Pointer to the Win::MIDI::Message::InputHeader::Queue

    //CRITICAL_SECTION criticalSection;       //< Thread stuff.
};

struct HMIDIOut
{
    char A;
};

class OutputHeader
{
    public:

    OutputHeader (HMIDIOut devHandle, byte* message, uint32_t length, bool &errorFlag);
    /*< Constructor.
		@param devHandle A handle to the MIDI input device.
        @param buffer    The buffer.
        @param length    The length of the buffer.
        @param errorFlag This is a variable that the user passes into the contstructor
            that is set true if there is an error createing
     */

    ~OutputHeader ();

    void sendMessage ();
    /*< Sends this message the portHandle. */


    private:

    HMIDIOut portHandle;    //< A handle to the port to send the midiHeader's message.
    MIDIHDR  midiHeader;    //< The header of the MIDI message to send.
};

class OutputHeaderQueue
/** A thread-safe queue for storing Win::MIDI::Message::OutputHeader objects. */
{
    public:

    OutputHeaderQueue ();
    ~OutputHeaderQueue ();

    void addHeader  (OutputHeader* oh);
    void removeHeader ();
    void removeAll ();
    bool isEmpty ();

    private:

    //CRITICAL_SECTION criticalSection;
};
}   //< namespace _midi
