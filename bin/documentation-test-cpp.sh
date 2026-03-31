#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

REDON=$(tput setaf 1)
GREENON=$(tput setaf 2)
COLOROFF=$(tput sgr0)

(

    cd "${SCRIPT_DIR}" || exit

    cd ..

    printf "Running Documentation Tests\n"

    find ./Documentation -type f -name "*.cpp" | while read -r FILE; do

        printf " - Running %s ... " "${FILE}"

        if ! g++ -std=c++17 -o test "${FILE}" -Iinclude; then
            printf "%sFAILED%s\n" "${REDON}" "${COLOROFF}"
            exit 1
        fi

        printf "%sOK%s\n" "${GREENON}" "${COLOROFF}"

        rm test

    done

)
