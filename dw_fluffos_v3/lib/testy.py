import os
from pathlib import Path

def merge_files(source_dir, extensions, output_file, separator="=" * 50):
    """
    Merge files with specified extensions from source_dir into output_file.
    
    Args:
        source_dir (str): Directory to scan
        extensions (tuple): File extensions to process (e.g., ('.c',))
        output_file (str): Path to output merged file
        separator (str): Separator between file contents
    """
    # Convert to Path object
    dir_path = Path(source_dir)
    
    if not dir_path.exists():
        print(f"Directory {source_dir} does not exist!")
        return
    
    try:
        with open(output_file, 'w', encoding='utf-8') as outfile:
            file_count = 0
            
            # Walk through directory tree
            for root, dirs, files in os.walk(source_dir):
                for filename in sorted(files):  # Sort for consistent ordering
                    if filename.lower().endswith(extensions):
                        filepath = os.path.join(root, filename)
                        
                        # Write header with filename
                        relative_path = os.path.relpath(filepath, source_dir)
                        outfile.write(f"\n{separator}\n")
                        outfile.write(f"FILE: {relative_path}\n")
                        outfile.write(f"{separator}\n\n")
                        
                        # Write file contents
                        try:
                            with open(filepath, 'r', encoding='utf-8') as infile:
                                outfile.write(infile.read())
                                outfile.write("\n")  # Ensure newline at end
                            file_count += 1
                        except Exception as e:
                            print(f"Error reading {filepath}: {str(e)}")
            
            print(f"Merged {file_count} files into {output_file}")
            
    except Exception as e:
        print(f"Error writing to {output_file}: {str(e)}")

def main():
    # Base directory
    base_dir = "/mnt/home2/test/Test/dw_fluffos_v3/lib/"
    
    # Verify base directory exists
    if not os.path.exists(base_dir):
        print(f"Base directory {base_dir} does not exist!")
        return
    
    print("File Extraction and Merging Tool")
    print("===============================")
    
    # 1. Merge .c files from cmds and global into one file
    cmds_global_output = "merged_cmds_global.c"
    for folder in ['cmds', 'd', 'global']:
        folder_path = os.path.join(base_dir, folder)
        merge_files(folder_path, ('.c',), cmds_global_output)
    
    # 2. Merge .c files from obj and std into one file
    obj_std_output = "merged_obj_std.c"
    for folder in ['obj', 'std']:
        folder_path = os.path.join(base_dir, folder)
        merge_files(folder_path, ('.c',), obj_std_output)
    
    # 3. Merge .h files from include directory
    include_output = "merged_include.h"
    include_path = os.path.join(base_dir, 'include')
    merge_files(include_path, ('.h',), include_output)
    
    # 4. Merge .s files from soul directory
    soul_output = "merged_soul.s"
    soul_path = os.path.join(base_dir, 'soul')
    merge_files(soul_path, ('.s',), soul_output)
    
    print("\nExtraction and merging complete!")

if __name__ == "__main__":
    main()
