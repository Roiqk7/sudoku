#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Define red color code
RED='\033[0;31m'

echo "Setting up the project..."

# Function to check if Homebrew is installed and install it if it's not
install_homebrew()
{
        # Check if Homebrew is installed
        if ! command -v brew >/dev/null 2>&1; then
                echo "Homebrew not found. Installing Homebrew..."
                /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        else
                echo "Homebrew is already installed."
        fi
}

# Function to install dependencies using Homebrew
install_dependencies()
{
        echo "Installing dependencies using Homebrew..."

        # Install dependencies using Homebrew
        brew install cmake gcc googletest spdlog
}

# Detect operating system using uname
OS=$(uname -s)

# Check if the operating system is MacOS
if [ "${OS}" = "Darwin" ]; then
        # Install Homebrew if it's not installed
        install_homebrew

        # Install dependencies
        install_dependencies
else
        echo "${RED}[Error] This script is intended for MacOS users only."
fi