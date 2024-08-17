// File.h - Declares the File class.
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

#ifndef MIDI_DATA_FILE_H
#define MIDI_DATA_FILE_H

#include <string>
#include <vector>
#include <memory>
#include "BinData.h"
#include "FileHeaderData.h"
#include "Track.h"

namespace MidiData
{
    /// @brief Represents a MIDI file.
    class File : public BinData::RawFile
    {
    public:
        /// @brief Default constructor; creates a new instance of MidiData::File.
        /// @param fileName The path to the MIDI file.
        File(std::string fileName) : 
            BinData::RawFile{ fileName }, fileHeader{ BinData::Endianness::Big } 
        { }

        /// @brief Gets the MIDI file's header.
        /// @return The BinData::ChunkHeader representing the file header.
        BinData::ChunkHeader Header() { return fileHeader; }

        /// @brief Gets the MIDI file header's data.
        /// @return The data contained within the MIDI file's header.
        FileHeaderData HeaderData() { return headerData; }

        /// @brief Loads the MIDI file, including all headers and tracks.
        void Load();

        /// @brief Gets the tracks in the MIDI file.
        /// @return A vector that contains each MidiData::Track in the file.
        std::vector<Track> Tracks() { return tracks; }
    private:
        BinData::ChunkHeader fileHeader;
        FileHeaderData headerData;
        std::vector<Track> tracks;
    };
}

#endif