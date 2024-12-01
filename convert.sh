#!/bin/bash

# Check if folder path is provided
if [ -z "$1" ]; then
    echo "Usage: $0 /path/to/folder"
    exit 1
fi

# Folder path
FOLDER="$1"

# Loop through all files in the folder
for file in "$FOLDER"/*; do
    # Check if it's a regular file
    if [ -f "$file" ]; then
        # Convert from Windows-1251 to UTF-8 and save to a temporary file
        iconv -f WINDOWS-1251 -t UTF-8 "$file" -o "${file}.utf8"

        # Check if conversion was successful
        if [ $? -eq 0 ]; then
            # Overwrite original file with converted file
            mv "${file}.utf8" "$file"
            echo "Converted $file to UTF-8"
        else
            # If conversion failed, remove the temporary file
            rm "${file}.utf8"
            echo "Failed to convert $file"
        fi
    fi
done
