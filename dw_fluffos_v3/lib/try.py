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

def merge_files(source_dir, extensions, base_output_name, output_dir, char_limit=60000, token_limit=80000, separator="=" * 50):
    """Merge files into output_file(s) in output_dir, splitting when approaching char_limit."""
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
            if filename.lower().endswith(extensions):
                filepath = os.path.join(root, filename)
                
                try:
                    with open(filepath, 'r', encoding='utf-8') as infile:
                        content = infile.read()
                        header = f"\n{separator}\nFILE: {os.path.relpath(filepath, source_dir)}\n{separator}\n\n"
                        full_entry = header + content + "\n"
                        tokens_in_file = estimate_tokens(full_entry)
                        lines_in_file = count_lines(full_entry)
                        chars_in_file = count_chars(full_entry)
                except Exception as e:
                    print(f"Error reading {filepath}: {str(e)}")
                    continue
                
                print(f"Processing {filepath}: ~{tokens_in_file} tokens, {lines_in_file} lines, {chars_in_file} chars")
                
                if current_char_count + chars_in_file > char_limit or current_token_count + tokens_in_file > token_limit:
                    if outfile:
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
                
                if current_char_count == 0:
                    output_file = os.path.join(output_dir, f"{base_name}{'' if current_file_num == 1 else current_file_num}{ext}")
                    if outfile:
                        outfile.close()
                    outfile = open(output_file, 'w', encoding='utf-8')
                    print(f"Starting new file: {output_file}")
                    outfile.write("\n\n\n\n")  # Reserve space for header
                    
                outfile.write(full_entry)
                current_token_count += tokens_in_file
                current_char_count += chars_in_file
                file_count += 1
                files_in_current.append(filename)
    
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
    
    extensions = ('.c', '.h', '.s')
    
    directories = {
        'cmds': 'cmds_merged.txt',
        'd': 'd_merged.txt',
        'global': 'global_merged.txt',
        'obj': 'obj_merged.txt',
        'std': 'std_merged.txt',
        'secure': 'secure_merged.txt',
        'soul': 'soul_merged.txt'
    }
    
    print("File Extraction and Merging Tool (Optimized for Grok)")
    print("====================================================")
    print("Grok Limits:")
    print("- Maximum Context Window: 128,000 tokens")
    print("- Safe Cutoff Used: 60,000 chars or 80,000 tokens per file")
    print("- No strict line limit, but monitored")
    print("- Token estimation: Conservative (max(words/0.75, chars/4) * 1.2)")
    print(f"Output Directory: {output_dir}")
    print("====================================================")
    
    for dir_name, output_file in directories.items():
        folder_path = os.path.join(base_dir, dir_name)
        print(f"\nProcessing directory: {folder_path}")
        merge_files(folder_path, extensions, output_file, output_dir, char_limit=60000, token_limit=80000)
    
    print("\nExtraction and merging complete! All files are in", output_dir)

if __name__ == "__main__":
    main()
