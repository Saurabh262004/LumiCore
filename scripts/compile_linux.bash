#!/usr/bin/env bash

set -e

BUILD_DIR="example/build/linux"
CMAKE_ARGS=(-DCMAKE_BUILD_TYPE=Release)

while getopts "t" opt; do
	case "$opt" in
		t) CMAKE_ARGS+=(-DLUMI_BUILD_TESTAPP=ON) ;;
		*) echo "Usage: $0 [-t]" >&2; exit 1 ;;
	esac
done

cmake -B "$BUILD_DIR" -S . "${CMAKE_ARGS[@]}"
cmake --build "$BUILD_DIR"
