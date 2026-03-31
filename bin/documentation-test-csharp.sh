#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

REDON=$(tput setaf 1)
GREENON=$(tput setaf 2)
COLOROFF=$(tput sgr0)

(

    cd "${SCRIPT_DIR}" || exit

    cd ..

    printf "Running Documentation Tests\n"

    find ./Documentation.Tests/ -type f -name "*.cs" -exec rm {} \;

    find ./Documentation -type f -name "*.cs" | while read -r FILE; do

        printf " - Running %s ... " "${FILE}"

        cp "${FILE}" Documentation.Tests/

        if ! dotnet build Documentation.Tests/Documentation.Tests.csproj &> /dev/null; then
            printf "%sFAILED%s\n" "${REDON}" "${COLOROFF}"
            exit 1
        fi

        printf "%sOK%s\n" "${GREENON}" "${COLOROFF}"

        rm "Documentation.Tests/$(basename "${FILE}")"

    done

)
