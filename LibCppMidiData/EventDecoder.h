// EventDecoder.h - Declares the EventDecoder class.
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

#ifndef MIDI_DATA_EVENT_DECODER_H
#define MIDI_DATA_EVENT_DECODER_H

#include <vector>
#include <deque>
#include <memory>
#include "Decoder.h"
#include "EventType.h"

namespace MidiData
{
    class EventDecoder : public Decoder
    {
    public:
        EventDecoder() : 
            size{ 0 }, 
            bytesDecoded{ 0 },
            type{ EventType::Unknown },
            typeText{ "" }, 
            details{ "" }, 
            dataText{ "" },
            hasDecoded{ false }
        { }

        /// @brief The amount of bytes the decoder is expected to decode.
        /// @return The number of bytes. 
        virtual size_t Size() override;

        /// @brief Determines whether or not the decoder has already decoded data.
        /// @return Returns true if decoding has completed, otherwise false.
        virtual bool HasDecoded() override;

        virtual size_t BytesDecoded() override;

        /// @brief Provides a string representation of the decoded data.
        /// @return The string representing the decoded data.
        virtual std::string ToString() override;

        virtual std::string Details();

        virtual std::string TypeText();

        virtual EventType Type();
    protected:
        size_t size;
        size_t bytesDecoded;
        EventType type;
        std::string typeText;
        std::string details;
        std::string dataText;
        bool hasDecoded;
        std::vector<std::shared_ptr<Decoder>> subDecoders;
        std::deque<std::shared_ptr<Decoder>> decodeQueue;
        //std::unique_ptr<MidiEventDecoder> subDecoder;

        virtual bool HasSubDecoders() override;

        virtual std::shared_ptr<Decoder> NextSubDecoder() override;

        virtual BinData::UInt8Field ReadDataByte(BinData::FileStream* s);

        virtual void DecodeDataByte(std::string label, BinData::FileStream* s);

        virtual void DecodeDataField(std::string label, 
                                    BinData::Field* f, 
                                    BinData::FileStream* s);

        virtual void UpdateTypeInfo(EventDecoder* subDecoder);

        //virtual void FinishDecoding(BinData::FileStream* s) override;
    };
}



#endif