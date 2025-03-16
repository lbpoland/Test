import os
import re

# Configuration
BASE_PATH = "/mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/"
DIRS = ["player", "living", "guild-race"]
OUTPUT_BASE = "commands_part"
CHAR_LIMIT = 80000  # Cap at 80,000 characters
TOKEN_LIMIT = 120000  # Cap at 120,000 tokens (words)
BUFFER = 0.95  # 95% of limits as threshold (76,000 chars, 114,000 tokens)

def count_tokens(text):
    """Count tokens as words split by whitespace."""
    return len(re.split(r'\s+', text.strip()))

def process_files():
    # Collect all files
    all_files = []
    for dir_name in DIRS:
        dir_path = os.path.join(BASE_PATH, dir_name)
        for root, _, files in os.walk(dir_path):
            for file in files:
                all_files.append(os.path.join(root, file))

    # Process files into output files
    part_num = 1
    current_file = f"{OUTPUT_BASE}{part_num}.txt"
    char_count = 0
    token_count = 0
    with open(current_file, 'w', encoding='utf-8') as out_f:
        for file_path in all_files:
            try:
                with open(file_path, 'r', encoding='utf-8') as in_f:
                    content = in_f.read()
                    chars = len(content)
                    tokens = count_tokens(content)
                    
                    # Check if adding this file exceeds limits (with buffer)
                    if (char_count + chars > CHAR_LIMIT * BUFFER) or (token_count + tokens > TOKEN_LIMIT * BUFFER):
                        print(f"File {current_file} reached limits: {char_count} chars, {token_count} tokens")
                        part_num += 1
                        current_file = f"{OUTPUT_BASE}{part_num}.txt"
                        char_count = 0
                        token_count = 0
                        out_f.close()
                        out_f = open(current_file, 'w', encoding='utf-8')

                    # Write file path and content
                    out_f.write(f"\n=== {file_path} ===\n")
                    out_f.write(content)
                    out_f.write("\n")
                    char_count += chars + len(file_path) + 10  # Approx overhead for path and separators
                    token_count += tokens

            except Exception as e:
                print(f"Error reading {file_path}: {e}")

    print(f"Final file {current_file}: {char_count} chars, {token_count} tokens")
    out_f.close()

if __name__ == "__main__":
    process_files()
