# manifests.py
# Description: This script generates firmware manifests for each release of a GitHub repository.

import os
import json
import requests
from pathlib import Path

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

# Function to generate a manifest for each release
def generate_manifest(release, output_dir):
    tag_name = release.get("tag_name")
    assets = release.get("assets", [])

    for asset in assets:
        if asset["name"].endswith(".bin"):
            manifest = MANIFEST_TEMPLATE.copy()
            manifest["version"] = tag_name
            manifest["builds"] = [
                {
                    "chipFamily": "ESP32-S3",
                    "parts": [{"path": asset["name"], "offset": 0}],
                }
            ]

            # Write the manifest to a JSON file
            manifest_filename = os.path.join(output_dir, f"{tag_name}.json")
            with open(manifest_filename, "w") as f:
                json.dump(manifest, f, indent=2)
            print(f"Generated manifest: {manifest_filename}")

# Main script
def main():
    # Environment variable for GitHub token (optional for private repos)
    auth_token = os.getenv("GITHUB_TOKEN")

    # Ensure output directory exists
    output_path = Path(OUTPUT_DIR)
    output_path.mkdir(parents=True, exist_ok=True)

    try:
        # Fetch releases from GitHub
        releases = fetch_releases(GITHUB_API_URL, auth_token)

        # Generate manifests for each release
        for release in releases:
            generate_manifest(release, OUTPUT_DIR)

        print("All manifests generated successfully.")
    except requests.RequestException as e:
        print(f"Error fetching releases: {e}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

if __name__ == "__main__":
    main()
