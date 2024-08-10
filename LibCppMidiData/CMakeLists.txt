# CMakeLists.txt - Builds the LibCppMidiData library.
#
# Copyright (C) 2024 Stephen Bonar
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http ://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissionsand
# limitations under the License.

# Define the source files needed to build the library
set(LIB_SOURCES
    ChannelMessage.cpp
    NoteOnMessage.cpp
    ControlChangeMessage.cpp
    PitchWheelChangeMessage.cpp
    Decoder.cpp
    EndOfTrackEvent.cpp
    Event.cpp
    EventDecoder.cpp
    File.cpp
    Message.cpp
    MetaEvent.cpp
    ProgramChangeMessage.cpp
    SystemMessage.cpp
    TempoChangeEvent.cpp
    Track.cpp 
    TrackEvent.cpp
    StatusByte.cpp
    VariableLengthQuantity.cpp)

# Configure the library build target.
add_library(LibCppMidiData ${LIB_SOURCES})

# Define the additional libraries the GUI needs to link with. 
set(LIBRARIES LibCppBinData)

# Defines the locations of header files to include.
set (INCLUDES
    .
    ${PROJECT_SOURCE_DIR}/LibCppBinData/LibCppBinData)

# Override the default behavior of prefixing "lib" on the library binary so
# we end up with LibCppMidiData.a isntead of libLibCppMidiData.a.
set_target_properties(LibCppMidiData PROPERTIES PREFIX "")

# Include all the directories that contain headers that we need that are not
# in the current directory, otherwise the compiler won't find them
target_include_directories(LibCppMidiData PUBLIC ${INCLUDES})

# Links the executable with the libraries. 
target_link_libraries(LibCppMidiData ${LIBRARIES})