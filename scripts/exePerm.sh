#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

echo "Adding execute permissions to all scripts in the scripts directory..."

# Directory containing the scripts
SCRIPTS_DIR="./scripts"

# Loop through all files in the scripts directory
for script in "$SCRIPTS_DIR"/*; do
        # Check if the file is a regular file (not a directory or a link)
        if [ -f "$script" ]; then
                echo "Adding execute permission to $script"
                chmod +x "$script"
        fi
done

echo "All scripts in $SCRIPTS_DIR have been given execute permissions."