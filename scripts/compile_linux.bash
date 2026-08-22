#!/usr/bin/env bash

set -e

RUN="${1:-no}"
NVIDIA="${2:-no}"

BUILD_DIR="build/linux"

cmake -B "$BUILD_DIR" -S . -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR"

OUT="$BUILD_DIR/app"

if [[ "$RUN" == "-r" ]]; then
	if [[ "$NVIDIA" == "-n" ]]; then
		__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia "$OUT"
	else
		"$OUT"
	fi
fi
