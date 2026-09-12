#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    cd "${SCRIPT_DIR}" || exit

    . find-emscripten.sh

    cd ..

    cat > "compile_flags.txt" << EOF
-std=c++17
-I${EMSCRIPTEN_INCLUDE_PATH}
EOF

)
