#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    cd "${SCRIPT_DIR}" || exit

    cd ..

    (
        cd UnityPackage

        find . -type f -name "*.cs" -not -path '*/Editor/*' -not -path '*/Samples~/*' | while read -r FILE; do
            DIRECTORY=$(dirname "${FILE}")

            mkdir -p "../RhythmGameUtilities/${DIRECTORY}"

            cp -R "${FILE}" "../RhythmGameUtilities/${FILE}"
        done
    )

)
