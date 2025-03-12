import os
import re
import shutil
from pathlib import Path

def remove_comments(content):
    """
    Remove both multi-line (/* */) and single-line (//) comments from C code.
    """
    # First, handle multi-line comments
    # This regex matches /* ... */ including newlines
    content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
    
    # Then handle single-line comments
    # Split into lines and process each line
    lines = content.split('\n')
    cleaned_lines = []
    
    for line in lines:
        # Remove // comments and trailing whitespace
        cleaned_line = re.sub(r'//.*$', '', line).rstrip()
        if cleaned_line:  # Only keep non-empty lines
            cleaned_lines.append(cleaned_line)
    
    return '\n'.join(cleaned_lines)

def process_file(filepath):
    """
    Process a single file, removing comments and writing back if changed.
    """
    try:
        # Read the original content
        with open(filepath, 'r', encoding='utf-8') as f:
            original_content = f.read()
        
        # Remove comments
        new_content = remove_comments(original_content)
        
        # Only write back if content has changed
        if new_content != original_content:
            # Create backup
            backup_path = f"{filepath}.bak"
            shutil.copy2(filepath, backup_path)
            
            # Write the new content
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(new_content)
            
            print(f"Processed: {filepath} (backup created at {backup_path})")
        else:
            print(f"No changes needed: {filepath}")
            
    except Exception as e:
        print(f"Error processing {filepath}: {str(e)}")

def scan_directory(directory):
    """
    Recursively scan directory and process all .c and .h files.
    """
    # Convert to Path object for easier handling
    dir_path = Path(directory)
    
    if not dir_path.exists():
        print(f"Directory {directory} does not exist!")
        return
    
    # File extensions to process
    extensions = ('.c', '.h')
    
    # Counter for processed files
    file_count = 0
    
    print(f"Scanning directory: {directory}")
    
    # Walk through directory tree
    for root, dirs, files in os.walk(directory):
        for filename in files:
            if filename.lower().endswith(extensions):
                filepath = os.path.join(root, filename)
                process_file(filepath)
                file_count += 1
    
    print(f"\nProcessing complete. Total files processed: {file_count}")

def main():
    # Modified directory path
    lib_directory = "/mnt/home2/test/Test/dw_fluffos_v3/lib/"
    
    print("C/H Comment Removal Tool")
    print("=======================")
    
    # Confirm with user
    response = input(f"This will process all .c and .h files in {lib_directory} "
                    "and create backups. Continue? (y/n): ")
    
    if response.lower() != 'y':
        print("Operation cancelled.")
        return
    
    scan_directory(lib_directory)

if __name__ == "__main__":
    main()
