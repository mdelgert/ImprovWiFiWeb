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
    return (
        os.path.basename(filepath) in excluded_files
        or any(excluded_dir in filepath for excluded_dir in excluded_dirs)
    )

# Generate a list of all files in the embedded_dir, excluding unwanted files and directories
embed_files = []
for root, dirs, files in os.walk(embedded_dir):
    # Exclude unwanted directories
    dirs[:] = [d for d in dirs if d not in excluded_dirs]

    for file in files:
        filepath = os.path.relpath(os.path.join(root, file), start=embedded_dir)
        if not should_exclude(filepath):
            embed_files.append(f"{embedded_dir}/{filepath}")

# Read the existing platformio.ini
with open(platformio_file, "r") as f:
    lines = f.readlines()

# Remove the existing board_build.embed_files section
new_lines = []
inside_embed_files_section = False
for line in lines:
    if line.strip().startswith("board_build.embed_files ="):
        inside_embed_files_section = True
        new_lines.append("board_build.embed_files =\n")
        for file in embed_files:
            new_lines.append(f"    {file}\n")
    elif inside_embed_files_section and line.startswith("    "):
        continue  # Skip existing entries in the embed_files section
    else:
        inside_embed_files_section = False
        new_lines.append(line)

# If the section was not found, append it
if not any(line.strip().startswith("board_build.embed_files =") for line in new_lines):
    new_lines.append("\nboard_build.embed_files =\n")
    for file in embed_files:
        new_lines.append(f"    {file}\n")

# Write back to platformio.ini
with open(platformio_file, "w") as f:
    f.writelines(new_lines)

print(f"Updated {platformio_file} with embedded files.")
