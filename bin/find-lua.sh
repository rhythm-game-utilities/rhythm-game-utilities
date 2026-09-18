#!/bin/bash

[[ ! -d "${LUA_PATH}" && -d "/opt/homebrew/Cellar/lua/" ]] &&
    LUA_PATH=$(find /opt/homebrew/Cellar/lua/ -name "5.*" -type d | head -n 1)

[ ! -d "${LUA_PATH}" ] && echo "lua not found!" && exit 1

LUA_INCLUDE_PATH="${LUA_PATH}/include"

export LUA_PATH
export LUA_INCLUDE_PATH

echo "lua found at ${LUA_PATH}"

[[ ! -d "${LUAJIT_PATH}" && -d "/opt/homebrew/Cellar/luajit/" ]] &&
    LUAJIT_PATH=$(find /opt/homebrew/Cellar/luajit/ -name "2.*" -type d | head -n 1)

[ ! -d "${LUAJIT_PATH}" ] && echo "luajit not found!" && exit 1

LUAJIT_INCLUDE_PATH="${LUAJIT_PATH}/include"

export LUAJIT_PATH
export LUAJIT_INCLUDE_PATH

echo "luajit found at ${LUAJIT_PATH}"
