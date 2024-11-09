#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Define color codes
RED='\033[0;31m'
GREEN='\033[0;32m'

echo "Checking if the build was successful..."

# Initialize the build status flag optimistically
build_success=1

# Check the necessary dependencies
# Check if homebrew is installed
if ! command -v brew >/dev/null 2>&1; then
        echo "${RED}[Error] Homebrew is not installed."
        build_success=0
fi

# Check the necessary directories and files
# Check if the build directory exists
if [ ! -d "build" ]; then
        echo "${RED}[Error] The build directory does not exist."
        build_success=0
# Check if the build directory is empty
elif [ -z "$(ls -A build)" ]; then
        echo "${RED}[Error] The build directory is empty."
        build_success=0
# Check if the project executable exists
elif [ ! -f "build/dungeonLife" ]; then
        echo "${RED}[Error] The project executable does not exist."
        build_success=0
fi

# Check the build status flag and print the final status
if [ $build_success -eq 1 ]; then
        echo -e "${GREEN}Build was successful.${NC}"
else
        echo -e "${RED}Build failed.${NC}"
fi

# Exit with the appropriate status code
exit $build_success