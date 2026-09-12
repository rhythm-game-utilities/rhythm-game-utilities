#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

REDON=$(tput setaf 1)
GREENON=$(tput setaf 2)
YELLOWON=$(tput setaf 3)
COLOROFF=$(tput sgr0)

(

    cd "${SCRIPT_DIR}" || exit

    cd ..

    npm install

    npm run postinstall

    printf "Running Documentation Tests\n"

    find ./Documentation -type f -name "*.js" | while read -r FILE; do

        printf " - Running %s ... " "${FILE}"

        EXPECTED_FILE="${FILE%.js}.txt"

        if [ -s "${FILE}" ]; then

            if ! OUTPUT=$(node "${FILE}" 2>&1); then
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

        else

            printf "%sSKIP%s\n" "${YELLOWON}" "${COLOROFF}"

        fi

    done

)
