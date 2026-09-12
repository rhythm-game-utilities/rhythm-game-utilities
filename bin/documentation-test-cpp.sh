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

        EXPECTED_FILE="${FILE%.cpp}.txt"

        if ! g++ -std=c++17 -o test "${FILE}" -Iinclude; then
            printf "%sFAILED%s\n" "${REDON}" "${COLOROFF}"
            exit 1
        fi

        if ! OUTPUT=$(./test 2>&1); then
            printf "%sFAILED%s\n" "${REDON}" "${COLOROFF}"

            echo "${OUTPUT}"

            exit 1
        fi

        if [ -s "${EXPECTED_FILE}" ]; then

            if ! DIFF_OUTPUT=$(diff -u "${EXPECTED_FILE}" <(echo "${OUTPUT}")); then
                printf "%sFAILED%s\n" "${REDON}" "${COLOROFF}"

                echo "${DIFF_OUTPUT}"

                exit 1
            fi

        else

            echo "${OUTPUT}" >> "${EXPECTED_FILE}"

        fi

        printf "%sOK%s\n" "${GREENON}" "${COLOROFF}"

        rm test

    done

)
