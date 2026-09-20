#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    cd "${SCRIPT_DIR}" || exit

    cd ..

    mkdir -p dist/

    em++ -O3 --bind -s MODULARIZE=1 -s EXPORT_ES6=1 main.cpp -I../include/ -o dist/module.mjs --emit-tsd module.d.ts

    ./node_modules/.bin/tsc

    if [[ "${OSTYPE}" == "darwin"* ]]; then
      sed -i '' "s/@rhythm-game-utilities\/core\/module/.\/module.mjs/g" dist/index.js
    else
      sed -i "s/@rhythm-game-utilities\/core\/module/.\/module.mjs/g" dist/index.js
    fi

)
