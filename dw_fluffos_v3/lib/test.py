import os
import tokenize
from io import BytesIO

# Base directory for the lib files
LIB_DIR = "/mnt/home2/test/Test/dw_fluffos_v3/lib/"
OUTPUT_DIR = "/mnt/home2/test/Test/dw_fluffos_v3/lib/output/"  # Adjust as needed
MAX_CHARS = 80000
MAX_TOKENS = 120000

# List of files to extract (relative paths from LIB_DIR)
FILES_TO_EXTRACT = [
    "std/room/inherit/topography/aroom.c",
    "std/room/inherit/topography/iroom.c",
    "std/room/inherit/topography/milestone.c",
    "std/room/topography/area/mountain.c",
    "std/room/topography/area/outside.c",
    "std/room/topography/area/plain.c",
    "std/room/topography/area/room.c",
    "std/room/topography/area/water_inside.c",
    "std/room/topography/area/water_outside.c",
    "std/room/topography/area/woodland.c",
    "std/room/topography/iroom/mountain.c",
    "std/room/topography/iroom/outside.c",
    "std/room/topography/iroom/plain.c",
    "std/room/topography/iroom/room.c",
    "std/room/topography/iroom/woodland.c",
    "std/room/topography/milestone/mountain.c",
    "std/room/topography/milestone/outside.c",
    "std/room/topography/milestone/plain.c",
    "std/room/topography/milestone/room.c",
    "std/room/topography/milestone/woodland.c",
]

def count_tokens(file_content):
    """Count tokens in a file content string."""
    try:
        tokens = list(tokenize.tokenize(BytesIO(file_content.encode('utf-8')).readline))
        return len(tokens)
    except Exception as e:
        print(f"Error counting tokens: {e}")
        # Fallback: Approximate tokens as word count
        return len(file_content.split())

def extract_and_combine_files():
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

    current_file_num = 1
    current_output = ""
    current_chars = 0
    current_tokens = 0
    output_filename = f"{OUTPUT_DIR}extracted_files_part_{current_file_num}.txt"

    for rel_path in FILES_TO_EXTRACT:
        full_path = os.path.join(LIB_DIR, rel_path)
        if not os.path.exists(full_path):
            print(f"File not found: {full_path}")
            continue

        with open(full_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
            chars = len(content)
            tokens = count_tokens(content)

            # Check if adding this file exceeds limits
            if (current_chars + chars > MAX_CHARS) or (current_tokens + tokens > MAX_TOKENS):
                # Save current file and start a new one
                with open(output_filename, 'w', encoding='utf-8') as out_f:
                    out_f.write(current_output)
                print(f"Saved {output_filename}: {current_chars} chars, {current_tokens} tokens")

                # Reset for new file
                current_file_num += 1
                current_output = ""
                current_chars = 0
                current_tokens = 0
                output_filename = f"{OUTPUT_DIR}extracted_files_part_{current_file_num}.txt"

            # Add file content with a header
            current_output += f"\n\n=== {rel_path} ===\n\n{content}"
            current_chars += chars
            current_tokens += tokens
            print(f"Added {rel_path}: {chars} chars, {tokens} tokens (Total: {current_chars} chars, {current_tokens} tokens)")

    # Save the final file
    if current_output:
        with open(output_filename, 'w', encoding='utf-8') as out_f:
            out_f.write(current_output)
        print(f"Saved {output_filename}: {current_chars} chars, {current_tokens} tokens")

if __name__ == "__main__":
    extract_and_combine_files()
