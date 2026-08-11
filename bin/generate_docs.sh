#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    mkdir -p build/

    cd "${SCRIPT_DIR}" || exit

    cd ..

    {
        (cat "./Documentation/README.md" && printf '\n')
        (cat "./Documentation/Platforms.md" && printf '\n')
        (cat "./Documentation/Examples.md" && printf '\n')
        (cat "./Documentation/Install.md" && printf '\n')
    } > README.md

    printf "## API\n\n" >>README.md

    (cat "./Documentation/API/Audio/README.md" && printf '\n') >>README.md

    find ./Documentation/API/Audio -type f -name "*.md" -not -name "README.md" | sort -n |
        while read -r FILE; do
            (cat "${FILE}" && printf '\n') >>README.md
        done

    (cat "./Documentation/API/Common/README.md" && printf '\n') >>README.md

    find ./Documentation/API/Common -type f -name "*.md" -not -name "README.md" | sort -n |
        while read -r FILE; do
            (cat "${FILE}" && printf '\n') >>README.md
        done

    (cat "./Documentation/API/Parsers/README.md" && printf '\n') >>README.md

    find ./Documentation/API/Parsers -type f -name "*.md" -not -name "README.md" | sort -n |
        while read -r FILE; do
            (cat "${FILE}" && printf '\n') >>README.md
        done

    (cat "./Documentation/API/Utilities/README.md" && printf '\n') >>README.md

    find ./Documentation/API/Utilities -type f -name "*.md" -not -name "README.md" | sort -n |
        while read -r FILE; do
            (cat "${FILE}" && printf '\n') >>README.md
        done

    {
        (cat "./Documentation/Architecture.md" && printf '\n')
        (cat "./Documentation/Git Hooks.md" && printf '\n')
        (cat "./Documentation/Testing.md" && printf '\n')
        (cat "./Documentation/Build.md" && printf '\n')
        (cat "./Documentation/Contributing.md" && printf '\n')
        (cat "./Documentation/Community Roadmap.md" && printf '\n')
        (cat "./Documentation/Other Projects.md" && printf '\n')
        (cat "./Documentation/License.md" && printf '\n')
    } >> README.md

)
