#!/bin/bash

# Usage: ./build.sh [dev] [test]

# Exit immediately if a command exits with a non-zero status.
set -e

echo "Building the project..."

# Make all the scripts executable
chmod +x scripts/exePerm.sh
./scripts/exePerm.sh

# Set up the project (install dependencies)
./scripts/setup.sh

# Build the project with CMake
./scripts/build.sh "$@"

# Build the binary files
./scripts/bin.sh

# Run health test
./scripts/test.sh