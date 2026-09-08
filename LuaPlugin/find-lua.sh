#!/bin/bash

if [ -z "${LUA_PATH}" ] && [ -d "/opt/homebrew/Cellar/lua" ]; then
    export LUA_PATH=$(find /opt/homebrew/Cellar/lua -name "5.*" -type d | head -n 1)
fi

if [ ! -d "${LUA_PATH}" ]; then
    echo "lua not found at '${LUA_PATH}'!"
    exit 1
fi

export LUA_INCLUDE_PATH="${LUA_PATH}/include"

echo "lua found at ${LUA_PATH}"
