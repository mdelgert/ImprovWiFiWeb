#!/bin/bash

# Navigate to the website directory
cd ..
cd site

# Default action if no parameter is passed
ACTION=${1:-dev}

# Check the first argument passed to the script
if [ "$ACTION" == "dev" ]; then
  echo "Starting development server..."
  # Start the development server with Vite
  npm run dev
elif [ "$ACTION" == "build" ]; then
  echo "Building the project..."
  # Run the production build
  npm run build
elif [ "$ACTION" == "clean" ]; then
  echo "Cleaning the build directory..."
  # Clean the dist directory
  rm -rf dist
else
  echo "Usage: ./build.sh [dev|build|clean]"
  exit 1
fi
