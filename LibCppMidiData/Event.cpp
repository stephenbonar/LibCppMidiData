// Event.cpp - Defines the Event class.
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

#include "Event.h"

using namespace MidiData;

std::shared_ptr<StatusByte> Event::lastStatusByte;

void Event::StartDecoding(BinData::FileStream* s)
{
    statusByte = std::make_shared<StatusByte>();
    subDecoders.push_back(statusByte);
    decodeQueue.push_back(statusByte);
}

void Event::FinishDecoding(BinData::FileStream* s)
{
    if (!statusByte->IsValid())
    {
        if (Event::lastStatusByte != nullptr)
        {
            statusByte = Event::lastStatusByte;
            statusByte->SetIsRunning(true);
            typeText += "(Running)";
        }
        else
        {
            typeText += "Unknown";
            type = EventType::Unknown;
            dataText = statusByte->ToString();
            return;
        }
        
        // Go back one because we just consumed a data byte instead of a status
        // byte. The next decoder will need to consume this same byte.
        s->SetOffset(s->Offset() - 1);
    }
    else
    {
        dataText += statusByte->Value()->ToString(BinData::Format::Hex);
        Event::lastStatusByte = statusByte;
    }

    switch (statusByte->EventType())
    {
        case EventType::NoteOnMessage:
            midiMessage = std::make_shared<NoteOnMessage>(statusByte);
            break;
        case EventType::ControlChangeMessage:
            midiMessage = std::make_shared<ControlChangeMessage>(statusByte);
            break;
        case EventType::ProgramChangeMessage:
            midiMessage = std::make_shared<ProgramChangeMessage>(statusByte);
            break;
        case EventType::PitchWheelChangeMessage:
            midiMessage = std::make_shared<PitchWheelChangeMessage>(statusByte);
            break;
        case EventType::SystemMessage:
            midiMessage = std::make_shared<SystemMessage>(statusByte);
            break;
        default:
            typeText += "Unknown";
    }

    if (midiMessage != nullptr)
    {
        subDecoders.push_back(midiMessage);
        midiMessage->Decode(s);
        hasDecoded = true;
        CombineSubDecoderInfo(midiMessage.get());
    }
}