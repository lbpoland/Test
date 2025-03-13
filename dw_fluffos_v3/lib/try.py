import os
from pathlib import Path

def estimate_tokens(content):
    """Estimate token count with a conservative heuristic."""
    words = len(content.split())
    chars = len(content.replace('\n', ''))
    token_estimate = max(int(words / 0.75), int(chars / 4)) * 1.2
    return int(token_estimate)

def count_lines(content):
    """Count lines in content."""
    return len(content.splitlines())

def count_chars(content):
    """Count characters excluding newlines."""
    return len(content.replace('\n', ''))

def merge_files(source_dir, extensions, base_output_name, output_dir, char_limit=85000, token_limit=125000, separator="=" * 50):
    """Merge files into output_file(s) in output_dir, splitting when approaching limits."""
    dir_path = Path(source_dir)
    if not dir_path.exists():
        print(f"Directory {source_dir} does not exist!")
        return
    
    os.makedirs(output_dir, exist_ok=True)
    
    base_name, ext = os.path.splitext(base_output_name)
    
    current_file_num = 1
    current_token_count = 0
    current_char_count = 0
    file_count = 0
    outfile = None
    files_in_current = []
    
    for root, dirs, files in os.walk(source_dir):
        for filename in sorted(files):
            if filename.lower().endswith(extensions) and filename.strip() and filename != '.c':  # Skip empty or '.c'
                filepath = os.path.join(root, filename)
                
                try:
                    with open(filepath, 'r', encoding='utf-8') as infile:
                        content = infile.read()
                        # Get path relative to /lib/ (strip everything before /lib/)
                        full_rel_path = os.path.relpath(filepath, os.path.dirname(source_dir))
                        header = f"\n{separator}\nFILE: /lib/{full_rel_path}\n{separator}\n\n"
                        full_entry = header + content + "\n"
                        tokens_in_file = estimate_tokens(full_entry)
                        lines_in_file = count_lines(full_entry)
                        chars_in_file = count_chars(full_entry)
                except Exception as e:
                    print(f"Error reading {filepath}: {str(e)}")
                    continue
                
                print(f"Processing {filepath}: ~{tokens_in_file} tokens, {lines_in_file} lines, {chars_in_file} chars")
                
                # Check limits and close file if exceeded
                if outfile and (current_char_count + chars_in_file > char_limit or current_token_count + tokens_in_file > token_limit):
                    outfile.seek(0)
                    outfile.write(f"# Total Tokens: {current_token_count}\n"
                                  f"# Total Files Merged: {len(files_in_current)}\n"
                                  f"# Total Characters: {current_char_count}\n\n")
                    outfile.close()
                    print(f"Closed {output_file}: {len(files_in_current)} files, "
                          f"~{current_token_count} tokens, {current_char_count} chars")
                    current_file_num += 1
                    current_token_count = 0
                    current_char_count = 0
                    files_in_current = []
                    outfile = None
                
                # Open new file if none exists
                if not outfile:
                    output_file = os.path.join(output_dir, f"{base_name}{'' if current_file_num == 1 else current_file_num}{ext}")
                    outfile = open(output_file, 'w', encoding='utf-8')
                    print(f"Starting new file: {output_file}")
                    outfile.write("\n\n\n\n")  # Reserve space for header
                
                # Write file content with header
                outfile.write(full_entry)
                current_token_count += tokens_in_file
                current_char_count += chars_in_file
                file_count += 1
                files_in_current.append(filename)
            else:
                print(f"Skipped invalid filename: {filename}")
    
    # Finalize last file
    if outfile:
        outfile.seek(0)
        outfile.write(f"# Total Tokens: {current_token_count}\n"
                      f"# Total Files Merged: {len(files_in_current)}\n"
                      f"# Total Characters: {current_char_count}\n\n")
        outfile.close()
        print(f"Closed {output_file}: {len(files_in_current)} files, "
              f"~{current_token_count} tokens, {current_char_count} chars")
    print(f"Total: Merged {file_count} files across {current_file_num} output file(s) for {source_dir}")

def main():
    base_dir = "/mnt/home2/test/Test/dw_fluffos_v3/lib/"
    output_dir = os.path.join(base_dir, "merged")
    
    if not os.path.exists(base_dir):
        print(f"Base directory {base_dir} does not exist!")
        return
    
    c_directories = {
        'cmds': 'cmds_merged.txt',
        'd': 'd_merged.txt',
        'global': 'global_merged.txt',
        'obj': 'obj_merged.txt',
        'std': 'std_merged.txt',
        'secure': 'secure_merged.txt'
    }
    h_directories = {'include': 'include_merged.txt'}
    s_directories = {'soul': 'soul_merged.txt'}
    
    print("File Extraction and Merging Tool (Optimized for Grok)")
    print("====================================================")
    print("Grok Limits:")
    print("- Maximum Context Window: 128,000 tokens")
    print("- Safe Cutoff Used: 85,000 chars or 125,000 tokens per file")
    print("- No strict line limit, but monitored")
    print("- Token estimation: Conservative (max(words/0.75, chars/4) * 1.2)")
    print(f"Output Directory: {output_dir}")
    print("HELP: Headers show paths relative to /lib/ (e.g., /lib/obj/armour.c) for 2003 Discworld MUD lib.")
    print("      If you see an unnamed file block, check for empty or invalid files (e.g., 'find /lib/obj/ -type f -name \"*.c\" -empty').")
    print("====================================================")
    
    print("\nProcessing .c files:")
    for dir_name, output_file in c_directories.items():
        folder_path = os.path.join(base_dir, dir_name)
        print(f"\nProcessing directory: {folder_path}")
        merge_files(folder_path, ('.c',), output_file, output_dir, char_limit=85000, token_limit=125000)
    
    print("\nProcessing .h files:")
    for dir_name, output_file in h_directories.items():
        folder_path = os.path.join(base_dir, dir_name)
        print(f"\nProcessing directory: {folder_path}")
        merge_files(folder_path, ('.h',), output_file, output_dir, char_limit=85000, token_limit=125000)
    
    print("\nProcessing .s files:")
    for dir_name, output_file in s_directories.items():
        folder_path = os.path.join(base_dir, dir_name)
        print(f"\nProcessing directory: {folder_path}")
        merge_files(folder_path, ('.s',), output_file, output_dir, char_limit=85000, token_limit=125000)
    
    print("\nExtraction and merging complete! All files are in", output_dir)

if __name__ == "__main__":
    main()
