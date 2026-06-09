#!/bin/bash

# ==============================================================================
# ENVIRONMENT SETUP SCRIPT
# Target: Ubuntu Linux
# ==============================================================================

set -euo pipefail

echo "========================================="
echo "TimberMan Environment Setup"
echo "========================================="

# 1. OS Detection Check
if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS_NAME=$NAME
else
    OS_NAME=$(uname -s)
fi

# Check if target is Ubuntu
if [[ ! "$OS_NAME" =~ [Uu]buntu ]]; then
    echo "WARNING: This script is optimized for Ubuntu Linux."
    echo "Your current system ($OS_NAME) is not Ubuntu."
    echo "Please configure dependencies manually."
    echo "Required: g++, make, git, libsfml-dev"
    echo "========================================="
    exit 0
fi

echo "System verified as Ubuntu. Installing dependencies..."

# 2. Function to install if missing
install_if_missing() {
    local pkg_name=$1
    if dpkg -s "$pkg_name" >/dev/null 2>&1; then
        echo "Status: '$pkg_name' is already installed."
    else
        echo "Status: '$pkg_name' is missing. Installing..."
        sudo apt-get update -qq || true
        sudo apt-get install -y "$pkg_name"
    fi
}

# 3. Install required packages
for pkg in g++ make git libsfml-dev; do
    install_if_missing "$pkg"
done

echo "========================================="
echo "Setup completed successfully!"
echo "========================================="
