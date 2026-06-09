#!/bin/bash
# Exit on error
set -e

echo "Installing build tools and SFML on Ubuntu..."
sudo apt-get update
sudo apt-get install -y git g++ make libsfml-dev
echo "Setup complete!"
