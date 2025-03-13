import os
from pathlib import Path

def merge_files(source_dir, extensions, base_output_name, line_limit=30000, separator="=" * 50):
    """
    Merge files with specified extensions from source_dir into output_file(s),
    splitting into new files when approaching line_limit.
    
    Args:
        source_dir (str): Directory to scan
        extensions (tuple): File extensions to process
        base_output_name (str): Base name for output files (e.g., 'cmds_merged.txt')
        line_limit (int): Maximum lines before starting new file
        separator (str): Separator between file contents
    """
    # Convert to Path object
    dir_path = Path(source_dir)
    
    if not dir_path.exists():
        print(f"Directory {source_dir} does not exist!")
        return
    
    # Split base name and extension
    base_name, ext = os.path.splitext(base_output_name)
    
    current_file_num = 1
    current_line_count = 0
    file_count = 0
    outfile = None
    
    # Walk through directory tree
    for root, dirs, files in os.walk(source_dir):
        for filename in sorted(files):  # Sort for consistent ordering
            if filename.lower().endswith(extensions):
                filepath = os.path.join(root, filename)
                
                # Read file content and count lines
                try:
                    with open(filepath, 'r', encoding='utf-8') as infile:
                        content = infile.read()
                        lines_in_file = len(content.splitlines()) + 4  # Include header lines
                except Exception as e:
                    print(f"Error reading {filepath}: {str(e)}")
                    continue
                
                # Check if adding this file would exceed limit
                if current_line_count + lines_in_file > line_limit:
                    if outfile:
                        outfile.close()
                    current_file_num += 1
                    current_line_count = 0
                
                # Open new file if needed
                if current_line_count == 0:
                    output_file = f"{base_name}{'' if current_file_num == 1 else current_file_num}{ext}"
                    if outfile:
                        outfile.close()
                    outfile = open(output_file, 'w', encoding='utf-8')
                    print(f"Starting new file: {output_file}")
                
                # Write header and content
                relative_path = os.path.relpath(filepath, source_dir)
                outfile.write(f"\n{separator}\n")
                outfile.write(f"FILE: {relative_path}\n")
                outfile.write(f"{separator}\n\n")
                outfile.write(content)
                outfile.write("\n")  # Ensure newline at end
                
                current_line_count += lines_in_file
                file_count += 1
    
    if outfile:
        outfile.close()
        print(f"Merged {file_count} files across {current_file_num} output file(s) for {source_dir}")

def main():
    # Base directory
    base_dir = "/mnt/home2/test/Test/dw_fluffos_v3/lib/"
    
    # Verify base directory exists
    if not os.path.exists(base_dir):
        print(f"Base directory {base_dir} does not exist!")
        return
    
    # Extensions to process
    extensions = ('.c', '.h', '.s')
    
    # Directories to process and their output filenames
    directories = {
        'cmds': 'cmds_merged.txt',
        'd': 'd_merged.txt',
        'global': 'global_merged.txt',
        'obj': 'obj_merged.txt',
        'std': 'std_merged.txt',
        'secure': 'secure_merged.txt',
        'soul': 'soul_merged.txt'
    }
    
    print("File Extraction and Merging Tool (with Line Limit)")
    print("=================================================")
    
    # Process each directory
    for dir_name, output_file in directories.items():
        folder_path = os.path.join(base_dir, dir_name)
        print(f"\nProcessing directory: {folder_path}")
        merge_files(folder_path, extensions, output_file, line_limit=30000)
    
    print("\nExtraction and merging complete!")

if __name__ == "__main__":
    main()
