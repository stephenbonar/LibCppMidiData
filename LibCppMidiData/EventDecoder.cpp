// EventDecoder.cpp - Defines the EventDecoder class.
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

#include "EventDecoder.h"

using namespace MidiData;

bool EventDecoder::HasDecoded()
{
    for (std::shared_ptr<Decoder> subDecoder : subDecoders)
    {
        if (!subDecoder->HasDecoded())
            return false;
    }

    return hasDecoded;
}

size_t EventDecoder::Size()
{   
    size_t subDecoderSize{ 0 };

    for (std::shared_ptr<Decoder> subDecoder : subDecoders)
        subDecoderSize += subDecoder->Size();
    
    return size + subDecoderSize;
}

std::string EventDecoder::ToString()
{
    return dataText; 
}

std::string EventDecoder::Details()
{
    return details;
}

std::string EventDecoder::TypeText()
{
    return typeText;
}

EventType EventDecoder::Type()
{
    return type;
}

std::shared_ptr<Decoder> EventDecoder::NextSubDecoder()
{
    if (!decodeQueue.empty())
    {
        std::shared_ptr<Decoder> subDecoder = decodeQueue.front();
        decodeQueue.pop_front();
        return subDecoder;
    }
    else
    {
        return nullptr;
    }
}

bool EventDecoder::HasSubDecoders()
{
    if (!decodeQueue.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t EventDecoder::BytesDecoded()
{
    size_t subDecoderBytesDecoded{ 0 };

    if (subDecoders.size() > 0)
    {
        for (std::shared_ptr<Decoder> subDecoder : subDecoders)
            subDecoderBytesDecoded += subDecoder->BytesDecoded();
    }

    return bytesDecoded + subDecoderBytesDecoded;
}

BinData::UInt8Field EventDecoder::ReadDataByte(BinData::FileStream* s)
{
    BinData::UInt8Field byte;
    s->Read(&byte);
    dataText += byte.ToString(BinData::Format::Hex) + " ";
    return byte;
}

void EventDecoder::DecodeDataByte(std::string label, BinData::FileStream* s)
{
    BinData::UInt8Field byte = ReadDataByte(s);
    details += " " + label + " " + byte.ToString();
}

void EventDecoder::DecodeDataField(std::string label, 
                                       BinData::Field* f, 
                                       BinData::FileStream* s)
{
    s->Read(f);
    dataText += f->ToString(BinData::Format::Hex) + " ";
    details += " " + label + " " + f->ToString();
}

void EventDecoder::UpdateTypeInfo(EventDecoder* subDecoder)
{
    type = subDecoder->Type();
    typeText += " " + subDecoder->TypeText();
    dataText += " " + subDecoder->ToString();
    details += " " + subDecoder->Details();
}

/*
void MidiEventDecoder::FinishDecoding(BinData::FileStream* s)
{
    if (subDecoder != nullptr)
        subDecoder->Decode(s);
}*/