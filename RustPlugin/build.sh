#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(
    cd "${SCRIPT_DIR}" || exit

    SDK_PATH=$(xcrun --show-sdk-path)

    mkdir -p libs/

    bindgen ../include/RhythmGameUtilities/RhythmGameUtilities.cpp \
        -o src/bindings.rs \
        --allowlist-file ".*RhythmGameUtilities.*" \
        --blocklist-type "std::.*" \
        --blocklist-type "regex_traits.*" \
        --blocklist-item ".*PATTERN.*" \
        --opaque-type "std::.*" \
        -- \
        -x c++ \
        -std=c++17 \
        -Qunused-arguments \
        -isysroot "${SDK_PATH}" \
        -I../include
)
