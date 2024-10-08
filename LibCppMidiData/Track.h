// Track.h - Declares the Track class.
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

#ifndef MIDI_DATA_TRACK_H
#define MIDI_DATA_TRACK_H

#include <vector>
#include <memory>
#include "Decoder.h"
#include "TrackEvent.h"
#include "EventType.h"
#include "StatusByte.h"
#include "BinData.h"

namespace MidiData
{
    class Track : public Decoder
    {
    public:
        Track(std::shared_ptr<BinData::ChunkHeader> trackHeader) 
            : hasDecoded{ false }, trackHeader{ trackHeader } 
        { }

        virtual bool HasDecoded() override { return hasDecoded; }

        virtual size_t Size() override { return trackHeader->Size()->Value(); }

        virtual std::string ToString() override { return "Track"; }

        std::vector<std::shared_ptr<TrackEvent>> Events() { return events; }
    protected:
        virtual bool HasSubDecoders() override;

        virtual std::shared_ptr<Decoder> NextSubDecoder() override;

        virtual size_t BytesDecoded() override;

        virtual void FinishDecoding(BinData::FileStream* s) override;
    private:
        bool hasDecoded;
        std::shared_ptr<BinData::ChunkHeader> trackHeader;
        std::vector<std::shared_ptr<TrackEvent>> events;
    };
}

#endif