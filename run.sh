#!/usr/bin/env bash
set -euo pipefail

case "${1:-}" in
    "")
        cmake --build build --target run
        ;;
    generate)
        rm -rf build/CMakeCache.txt
        cmake -G Ninja -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
        ;;
    *)
        echo "Unknown argument: \"$1\""
        echo "Usage: $(basename "$0") [generate]"
        exit 1
        ;;
esac
