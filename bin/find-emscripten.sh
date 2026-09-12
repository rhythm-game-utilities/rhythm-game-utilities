#!/bin/bash

[[ ! -d "${EMSCRIPTEN_PATH}" && -d "/opt/homebrew/Cellar/emscripten/" ]] &&
    EMSCRIPTEN_PATH=$(find /opt/homebrew/Cellar/emscripten/ -name "6.*" -type d | head -n 1)

[ ! -d "${EMSCRIPTEN_PATH}" ] && echo "Emscripten not found!" && exit 1

EMSCRIPTEN_INCLUDE_PATH="${EMSCRIPTEN_PATH}/libexec/system/include"

export EMSCRIPTEN_PATH
export EMSCRIPTEN_INCLUDE_PATH

echo "EMSCRIPTEN found at ${EMSCRIPTEN_PATH}"
