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

        if [ -s "${FILE}" ]; then

            if ! OUTPUT=$(node "${FILE}" 2>&1); then
                printf "%sFAILED%s\n" "${REDON}" "${COLOROFF}"

                echo "${OUTPUT}"

                exit 1
            fi

            printf "%sOK%s\n" "${GREENON}" "${COLOROFF}"

        else

            printf "%sSKIP%s\n" "${YELLOWON}" "${COLOROFF}"

        fi

    done

)
