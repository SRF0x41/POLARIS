#!/bin/bash

# Navigate to the project directory
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"

# Ensure the build directory exists
mkdir -p "$BUILD_DIR"

# Move into the build directory
cd "$BUILD_DIR"

# Run program 
./POLARIS

