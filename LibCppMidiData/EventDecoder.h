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
    /// @brief A decoder for various types of MIDI events.
    ///
    /// Provides a basic, common decoder implementation for classes 
    /// representing MIDI events to inherit from, including data. Most data 
    /// is protected so derived types can access it directly. Most methods have
    /// a sufficient implementation so that derived types only need to override
    /// StartDecoding() and FinishDecoding() to provide implementation specific
    /// decoding functionality. 
    class EventDecoder : public Decoder
    {
    public:
        /// @brief Default constructor; creates a new instance of EventDecoder.
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

        /// @brief Determines the number of bytes that have been decoded so far. 
        /// @return The number of bytes. 
        virtual size_t BytesDecoded() override;

        /// @brief Provides a string representation of the decoded data.
        /// @return The string representing the decoded data.
        virtual std::string ToString() override;

        /// @brief Gets the details of the decoded data.
        ///
        /// Details provide a human readable interpretation of the event's
        /// decoded data. Someone should be able to read the details and
        /// understand exactly what the event is doing (which value the
        /// tempo is being set to, which specific note is being played, etc.).
        ///
        /// @return A string representing the details of the decoded data.
        virtual std::string Details();

        /// @brief Gets a text representation of the event's type. 
        /// @return A string representing the event's type. 
        virtual std::string TypeText();

        /// @brief Gets the type of event.
        /// @return The EventType that represents this specific type of event.
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

        /// @brief Determines if there are any more child decoders to decode.
        ///
        /// This method is called internally by the Decode() method.
        ///
        /// @return Returns true if there are any remaining decoders, else false.
        virtual bool HasSubDecoders() override;

        /// @brief Provides the next child decoder to decode.
        ///
        /// This method is called internally by the Decode() method to retrieve
        /// the next child decoder and decode the remainng data with it.
        ///
        /// @return A shared pointer to the next decoder, or nullptr if no more.
        virtual std::shared_ptr<Decoder> NextSubDecoder() override;

        /// @brief Reads one byte at the current position of the file stream.
        ///
        /// This method should be called when a data byte needs to be returned
        /// for additional processing rather than decoded directly. 
        ///
        /// @param s The file stream to read from.
        /// @return A BinData::UInt8Field representing the data byte. 
        virtual BinData::UInt8Field ReadDataByte(BinData::FileStream* s);

        /// @brief Decodes the next byte from the specified file stream.
        ///
        /// Decodes the next byte from the specified file stream, labeling the
        /// byte value and appending the labeled value to details. This helps
        /// build the human readible output of the Details() method.
        ///
        /// @param label The label to prefix the byte value with
        /// @param s The file stream to decode the byte from.
        virtual void DecodeDataByte(std::string label, BinData::FileStream* s);

        /// @brief Decodes the specified data field.
        ///
        /// Reads the specified data field from the specified file stream,
        /// adding the hexidecimal representation of the field to dataText,
        /// prefixing the field value with the specified label, and adding
        /// the labeled value to details. The decoded field will thus be
        /// part of the hexidecimal representation of the event via ToString(),
        /// as well as the human readible Details().
        /// 
        /// @param label The label to prefix the value of the decoded field.
        /// @param f The field to decode.
        /// @param s The file stream from which to decode the fied.
        virtual void DecodeDataField(std::string label, 
                                     BinData::Field* f, 
                                     BinData::FileStream* s);

        /// @brief Combines the sub-decoder's info with the event's info.
        ///
        /// Appends the sub-decoder's type text, data text, and details to
        /// this event's. Also sets this event's type to that of the
        /// sub-decoder's because the sub-decoder represents a more specific
        /// type.
        ///
        /// @param subDecoder The sub-decoder to combine info from.
        virtual void CombineSubDecoderInfo(EventDecoder* subDecoder);
    };
}



#endif