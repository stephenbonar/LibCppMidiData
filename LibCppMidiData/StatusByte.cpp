// StatusByte.cpp - Defines the StatusByte class.
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

#include "StatusByte.h"

using namespace MidiData;

size_t StatusByte::BytesDecoded()
{
    if (hasDecoded)
        return 1;
    else
        return 0;
}

EventType StatusByte::EventType()
{
    switch (byte->Value() >> StatusCodeTypeBitShift)
    {
        case EventControlChangeMessage:
            return EventType::ControlChangeMessage;
        case EventProgramChangeMessage:
            return EventType::ProgramChangeMessage;
        case EventPitchWheelChangeMessage:
            return EventType::PitchWheelChangeMessage;
        case EventNoteOnMessage:
            return EventType::NoteOnMessage;
        case EventSystemMessage:
            return EventType::SystemMessage;
        default:
            return EventType::Unknown;
    }
}

bool StatusByte::IsValid()
{  
    int maskedValue = byte->Value() & StatusCodeValidationMask;
    
    if (maskedValue == StatusCodeValidationMask)
        return true;
    else
        return false;
}

std::string StatusByte::ToString()
{
    if (byte != nullptr)
        return byte->ToString(BinData::Format::Hex);
    else
        return "";
}

void StatusByte::FinishDecoding(BinData::FileStream* s)
{
    s->Read(byte.get());    
}