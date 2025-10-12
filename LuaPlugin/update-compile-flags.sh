#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    cd "${SCRIPT_DIR}" || exit

    . find-lua.sh

    cat > "compile_flags.txt" << EOF
-std=c++17
-I../include/
-I${LUA_INCLUDE_PATH}
EOF

)
