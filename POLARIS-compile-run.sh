#!/bin/bash

# Navigate to the project directory
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"

# Ensure the build directory exists
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Run CMake only if necessary
if [[ ! -f CMakeCache.txt ]]; then
    cmake -DCMAKE_PREFIX_PATH=/home/acerlaptop1/Desktop/dev/libtorch-cxx11-abi-shared-with-deps-2.6.0+cu118/libtorch ..
fi

# Compile the project using all available cores
make -j$(nproc)

# Check if compilation was successful
if [[ $? -eq 0 ]]; then
    echo "Compilation successful!"
    echo "Running POLARIS..."
    ./POLARIS
    echo "End Run"
else
    echo "Compilation failed. Check errors above."
fi
