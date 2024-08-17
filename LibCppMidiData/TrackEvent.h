// TrackEvent.h - Declares the TrackEvent class.
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

#ifndef MIDI_DATA_TRACK_EVENT_H
#define MIDI_DATA_TRACK_EVENT_H

#include <string>
#include <sstream>
#include <memory>
#include "BinData.h"
#include "VariableLengthQuantity.h"
#include "Constants.h"
#include "EventType.h"
#include "Event.h"
#include "EventDecoder.h"

namespace MidiData
{
    /// @brief Represents a MIDI track event (MTrk).
    ///
    /// The MIDI track event or MTrk event is the highest level event in a MIDI
    /// track. 
    class TrackEvent : public EventDecoder
    {
    public:
        std::string DeltaTime();
    protected:
        virtual void StartDecoding(BinData::FileStream* s) override;

        virtual void FinishDecoding(BinData::FileStream* s) override;
    private:
        std::shared_ptr<VariableLengthQuantity> deltaTime;
        std::shared_ptr<Event> midiEvent;
    };
}

#endif