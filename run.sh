#!/usr/bin/env bash
set -e

if [ -z "$1" ]; then
    cmake --build build --target run
elif [ "${1,,}" = "generate" ]; then
    cmake -G Ninja -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
else
    echo "Unknown argument: \"$1\""
    echo "Usage: $(basename "$0") [generate]"
    exit 1
fi
