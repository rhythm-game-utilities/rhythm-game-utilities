#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

REDON=$(tput setaf 1)
GREENON=$(tput setaf 2)
COLOROFF=$(tput sgr0)

(

    cd "${SCRIPT_DIR}" || exit

    cd ..

    export LUA_CPATH="LuaPlugin/rhythmgameutilities.so"

    printf "Running Documentation Tests\n"

    find ./Documentation -type f -name "*.lua" | while read -r FILE; do

        printf " - Running %s ... " "${FILE}"

        if ! lua "${FILE}" &> /dev/null; then
            printf "%sFAILED%s\n" "${REDON}" "${COLOROFF}"
            exit 1
        fi

        printf "%sOK%s\n" "${GREENON}" "${COLOROFF}"

    done

)
