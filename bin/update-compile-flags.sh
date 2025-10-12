#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    cd "${SCRIPT_DIR}" || exit

    . find-emscripten.sh
    . find-lua.sh

    cd ..

    cat > "compile_flags.txt" << EOF
-std=c++17
-Iinclude/
-I${EMSCRIPTEN_INCLUDE_PATH}
-I${LUA_INCLUDE_PATH}
-I${LUAJIT_INCLUDE_PATH}
EOF

)
