#!/bin/bash

# Define the target directory
TARGET_DIR="/mnt/home2/test/Test/dw_fluffos_v3/lib/"
OUTPUT_FILE="$TARGET_DIR/liblist"

# Check if the directory exists
if [ ! -d "$TARGET_DIR" ]; then
    echo "Error: Directory '$TARGET_DIR' does not exist."
    exit 1
fi

echo "Listing all directories, subfolders, and files in '$TARGET_DIR' and saving to '$OUTPUT_FILE':"
echo "-------------------------------------------------------------"

# Remove existing liblist file if it exists
[ -f "$OUTPUT_FILE" ] && rm "$OUTPUT_FILE"

# Use 'find' to list everything recursively and save to file
find "$TARGET_DIR" -print | while read -r item; do
    # Strip the prefix /mnt/home2/test/Test/dw_fluffos_v3 from the path
    relative_path="${item#/mnt/home2/test/Test/dw_fluffos_v3}"
    if [ -d "$item" ]; then
        echo "Directory: $relative_path" >> "$OUTPUT_FILE"
        echo "Directory: $relative_path"  # Also display to terminal
    elif [ -f "$item" ]; then
        echo "File: $relative_path" >> "$OUTPUT_FILE"
        echo "File: $relative_path"  # Also display to terminal
    fi
done

echo "-------------------------------------------------------------"
echo "Listing complete. Output saved to '$OUTPUT_FILE'."
