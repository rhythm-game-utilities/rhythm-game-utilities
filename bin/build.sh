#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

REDON=$(tput setaf 1)
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

    if ! lipo -info build/libRhythmGameUtilities.dylib | grep -q "x86_64 arm64"; then
        printf "%sFAILED%s\n" "${REDON}" "${COLOROFF}"

        exit 1
    fi

    mkdir -p UnityPackage/Libs/macOS
    mkdir -p RhythmGameUtilities/Libs/macOS

    cp build/libRhythmGameUtilities.dylib UnityPackage/Libs/macOS
    cp build/libRhythmGameUtilities.dylib RhythmGameUtilities/Libs/macOS

    printf "%sDONE%s\n" "${GREENON}" "${COLOROFF}"

)
