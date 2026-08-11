#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

GREENON=$(tput setaf 2)
COLOROFF=$(tput sgr0)

(

    mkdir -p build/

    cd "${SCRIPT_DIR}" || exit

    cd ..

    printf "Building macOS libraries ... "

    g++ -std=c++17 -shared -fPIC -arch arm64 -arch x86_64 \
        -o build/libRhythmGameUtilities.dylib \
        include/RhythmGameUtilities/RhythmGameUtilities.cpp || exit 1

    mkdir -p UnityPackage/Libs/macOS
    mkdir -p RhythmGameUtilities/Libs/macOS

    cp build/libRhythmGameUtilities.dylib UnityPackage/Libs/macOS
    cp build/libRhythmGameUtilities.dylib RhythmGameUtilities/Libs/macOS

    printf "%sDONE%s\n" "${GREENON}" "${COLOROFF}"

)
