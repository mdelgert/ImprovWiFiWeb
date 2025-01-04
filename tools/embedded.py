import os

# Directory containing the embedded files
embedded_dir = "web"

# Output PlatformIO configuration file
platformio_file = "platformio.ini"

# Files and folders to exclude
excluded_files = ["package-lock.json", "package.json"]
excluded_dirs = ["node_modules", "dist"]

# Helper function to determine if a file should be excluded
def should_exclude(filepath):
    # Check if the file is in an excluded directory or file list
    for excluded_dir in excluded_dirs:
        if os.path.commonpath([filepath, excluded_dir]) == excluded_dir:
            return True
    return os.path.basename(filepath) in excluded_files

# Read the existing platformio.ini
with open(platformio_file, "r") as f:
    lines = f.readlines()

# Find or create the section for board_build.embed_files
embed_files_section = "board_build.embed_files ="
new_lines = []
found_embed_files = False

# Generate a list of all files in the embedded_dir, excluding unwanted files and directories
embed_files = []
for root, dirs, files in os.walk(embedded_dir):
    # Exclude unwanted directories
    dirs[:] = [d for d in dirs if d not in excluded_dirs]

    for file in files:
        filepath = os.path.relpath(os.path.join(root, file), start=embedded_dir)
        if not should_exclude(filepath):
            embed_files.append(f"{embedded_dir}/{filepath}")

# Write the embed_files list to platformio.ini
for line in lines:
    if embed_files_section in line:
        found_embed_files = True
        # Add dynamically generated file list
        new_lines.append(embed_files_section + "\n")
        for file in embed_files:
            new_lines.append(f"    {file}\n")
    else:
        new_lines.append(line)

# If the section was not found, append it
if not found_embed_files:
    new_lines.append("\n" + embed_files_section + "\n")
    for file in embed_files:
        new_lines.append(f"    {file}\n")

# Write back to platformio.ini
with open(platformio_file, "w") as f:
    f.writelines(new_lines)

print(f"Updated {platformio_file} with embedded files.")
