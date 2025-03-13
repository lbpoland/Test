#!/bin/bash

# Define the target directory
TARGET_DIR="/mnt/home2/test/Test/dw_fluffos_v3/lib/"

# Check if the directory exists
if [ ! -d "$TARGET_DIR" ]; then
    echo "Error: Directory '$TARGET_DIR' does not exist."
    exit 1
fi

echo "Removing all files ending with '.bak' in '$TARGET_DIR':"
echo "-------------------------------------------------------------"

# Find and remove files ending with '.bak'
find "$TARGET_DIR" -type f -name "*.bak" -exec rm -v {} \;

echo "-------------------------------------------------------------"
echo "Removal complete."
