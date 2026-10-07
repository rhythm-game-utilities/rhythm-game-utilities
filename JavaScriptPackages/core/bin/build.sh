#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    cd "${SCRIPT_DIR}" || exit

    cd ..

    mkdir -p dist/

    em++ -O3 --bind -s MODULARIZE=1 -s EXPORT_ES6=1 -s SINGLE_FILE main.cpp -I../../include/ -o dist/module.mjs --emit-tsd module.d.ts

)
