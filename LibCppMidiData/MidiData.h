// MidiData.h - The main LibCppMidiData library header file.
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

#ifndef MIDI_DATA_H
#define MIDI_DATA_H

#include "ChannelMessage.h"
#include "Constants.h"
#include "ControlChangeMessage.h"
#include "Decoder.h"
#include "EndOfTrackEvent.h"
#include "Event.h"
#include "EventDecoder.h"
#include "EventType.h"
#include "File.h"
#include "FileHeaderData.h"
#include "Message.h"
#include "MetaEvent.h"
#include "NoteOnMessage.h"
#include "PitchWheelChangeMessage.h"
#include "ProgramChangeMessage.h"
#include "StatusByte.h"
#include "SystemMessage.h"
#include "TempoChangeEvent.h"
#include "Track.h"
#include "TrackEvent.h"
#include "VariableLengthQuantity.h"

#endif