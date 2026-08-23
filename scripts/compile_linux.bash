#!/usr/bin/env bash

set -e

BUILD_DIR="example/build/linux"

cmake -B "$BUILD_DIR" -S . -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR"

OUT="$BUILD_DIR/app"
