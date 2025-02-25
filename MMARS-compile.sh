#!/bin/bash

# Navigate to the project directory
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"

# Ensure the build directory exists
mkdir -p "$BUILD_DIR"

# Move into the build directory
cd "$BUILD_DIR"

# Run CMake (reconfigure if needed)
cmake -DCMAKE_PREFIX_PATH=/home/acerlaptop1/Desktop/dev/libtorch-cxx11-abi-shared-with-deps-2.6.0+cu118/libtorch
cmake --build . --config Release

# Compile the project using all available cores
make -j$(nproc)

# Check if compilation was successful
if [[ $? -eq 0 ]]; then
    echo "Compilation successful!"
    echo "Running MMARS..."
    ./MMARS
    echo "End Run"
else
    echo "Compilation failed. Check errors above."
fi

