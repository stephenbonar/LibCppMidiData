# CMakeLists.txt - Builds the LibCppMidiData library and its tests.
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

# cmake v3.12 is the minimum needed for add_compile_definitions()
cmake_minimum_required(VERSION 3.14)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configure the project name and version, which is configured into the binary.
project(LibCppMidiData VERSION 0.51)

# Although the project command can natively pass the name and version into
# the program through the configure_file command, there is no native RELEASE
# or COPYRIGHT info, so we define that here to pass to configure_file.
set(LIBCPPMIDIDATA_RELEASE "Alpha")
set(LIBCPPMIDIDATA_COPYRIGHT "Copyright (C) 2024 Stephen Bonar")

# Configure the library build.
add_subdirectory(LibCppMidiData)

# Configure the LibCppBinData library dependency.
add_subdirectory(LibCppBinData)
