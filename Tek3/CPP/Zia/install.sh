#!/bin/bash
git submodule update --init --recursive
mkdir -p build; cd build && rm CMakeCache.txt && conan install .. --build=missing
if [[ "$OSTYPE" == "linux-gnu" ]]; then
    cmake .. && cmake --build . -- -j 4
elif [[ "$OSTYPE" == "msys" ]]; then
    cmake -G "Visual Studio 15 2017 Win64" .. -Wno-dev && cmake --build . --config Release
fi