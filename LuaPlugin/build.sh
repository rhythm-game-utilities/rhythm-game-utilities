#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    cd "${SCRIPT_DIR}" || exit

    . ../bin/find-lua.sh

    g++ -std=c++17 -shared -fPIC -arch arm64 -arch x86_64 -undefined dynamic_lookup -o rhythmgameutilities.so lua_bindings.cpp \
        -I../include \
        -I"${LUAJIT_INCLUDE_PATH}"

)
