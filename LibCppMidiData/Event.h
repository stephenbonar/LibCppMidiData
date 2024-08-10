// Event.h - Declares the Event class.
//
// Copyright (C) 2024 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MIDI_DATA_EVENT_H
#define MIDI_DATA_EVENT_H

#include <memory>
#include <string>
#include "EventDecoder.h"
#include "Message.h"
#include "NoteOnMessage.h"
#include "ControlChangeMessage.h"
#include "ProgramChangeMessage.h"
#include "PitchWheelChangeMessage.h"
#include "SystemMessage.h"
#include "StatusByte.h"

namespace MidiData
{
    class Event : public EventDecoder
    {
    protected:
        static std::shared_ptr<StatusByte> lastStatusByte;

        std::shared_ptr<StatusByte> statusByte;
        std::shared_ptr<Message> midiMessage;

        virtual void StartDecoding(BinData::FileStream* s) override;

        virtual void FinishDecoding(BinData::FileStream* s) override;
    };
}

#endif