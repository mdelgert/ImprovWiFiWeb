import os
import json
import requests
from pathlib import Path
import shutil

# Constants (You can adjust these for your project)
GITHUB_API_URL = "https://api.github.com/repos/mdelgert/ImprovWiFiWeb/releases"
OUTPUT_DIR = "site/dist/firmware"
MANIFEST_TEMPLATE = {
    "name": "Test",
    "home_assistant_domain": "esphome",
    "funding_url": "https://github.com/mdelgert/ImprovWiFiWeb",
    "new_install_prompt_erase": False,
}

# Function to fetch releases from GitHub API
def fetch_releases(api_url, auth_token=None):
    headers = {"Accept": "application/vnd.github.v3+json"}
    if auth_token:
        headers["Authorization"] = f"token {auth_token}"

    response = requests.get(api_url, headers=headers)
    response.raise_for_status()  # Raise an exception for HTTP errors
    return response.json()

# Function to download a binary file
def download_binary(url, output_file):
    response = requests.get(url, stream=True)
    response.raise_for_status()  # Raise an exception for HTTP errors

    with open(output_file, "wb") as f:
        for chunk in response.iter_content(chunk_size=8192):
            f.write(chunk)
    print(f"Downloaded binary: {output_file}")

# Function to generate a manifest and download binaries for each release
def generate_manifest_and_download(release, output_dir):
    tag_name = release.get("tag_name")
    assets = release.get("assets", [])

    for asset in assets:
        if asset["name"].endswith(".bin"):
            # Define the binary filename with tag name
            binary_filename = f"{tag_name}.bin"
            binary_filepath = os.path.join(output_dir, binary_filename)

            # Download the binary file
            download_binary(asset["browser_download_url"], binary_filepath)

            # Create the manifest
            manifest = MANIFEST_TEMPLATE.copy()
            manifest["version"] = tag_name
            manifest["builds"] = [
                {
                    "chipFamily": "ESP32-S3",
                    "parts": [{"path": binary_filename, "offset": 0}],
                }
            ]

            # Write the manifest to a JSON file
            manifest_filename = os.path.join(output_dir, f"{tag_name}.json")
            with open(manifest_filename, "w") as f:
                json.dump(manifest, f, indent=2)
            print(f"Generated manifest: {manifest_filename}")

# Function to clean the output directory
def clean_output_directory(output_dir):
    if os.path.exists(output_dir):
        shutil.rmtree(output_dir)
        print(f"Deleted existing directory: {output_dir}")
    os.makedirs(output_dir)
    print(f"Created fresh directory: {output_dir}")

# Main script
def main():
    # Environment variable for GitHub token (optional for private repos)
    auth_token = os.getenv("GITHUB_TOKEN")

    # Clean the output directory
    clean_output_directory(OUTPUT_DIR)

    try:
        # Fetch releases from GitHub
        releases = fetch_releases(GITHUB_API_URL, auth_token)

        # Generate manifests and download binaries for each release
        for release in releases:
            generate_manifest_and_download(release, OUTPUT_DIR)

        print("All manifests and binaries processed successfully.")
    except requests.RequestException as e:
        print(f"Error fetching releases: {e}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

if __name__ == "__main__":
    main()
