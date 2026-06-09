#!/bin/bash

# ==============================================================================
# ENVIRONMENT SETUP SCRIPT
# Target: Ubuntu Linux
# Actions: Idempotently installs compiler, make/cmake utilities, and libsfml-dev
# ==============================================================================

set -euo pipefail

echo "========================================="
echo "TimberMan Environment Setup Automation"
echo "========================================="

# 1. OS Detection Check
if [ -f /etc/os-release ]; then
    # Read OS release properties
    . /etc/os-release
    OS_NAME=$NAME
else
    OS_NAME=$(uname -s)
fi

echo "Detected System: $OS_NAME"

# Check if target is Ubuntu
if [[ ! "$OS_NAME" =~ [Uu]buntu ]]; then
    echo "------------------------------------------------------------------"
    echo "WARNING: This script is optimized for Ubuntu Linux."
    echo "Your current system ($OS_NAME) is not Ubuntu."
    echo "Please configure dependencies manually."
    echo "Required dependencies: g++ (GCC), make, cmake, and libsfml-dev (v2.5+)"
    echo "------------------------------------------------------------------"
    exit 0
fi

echo "System verified as Ubuntu. Commencing package verification and setup..."
echo ""

# 2. Function to check and install missing packages
install_if_missing() {
    local pkg_name=$1
    echo "Checking for package: $pkg_name"
    if dpkg -s "$pkg_name" >/dev/null 2>&1; then
        echo "Status: '$pkg_name' is already installed."
    else
        echo "Status: '$pkg_name' is missing. Installing..."
        # Request sudo update only once if needed
        sudo apt-get update -qq || true
        sudo apt-get install -y "$pkg_name"
        echo "Status: '$pkg_name' installed successfully."
    fi
    echo ""
}

# 3. Verify and install compiler and make tools
install_if_missing "g++"
install_if_missing "make"
install_if_missing "cmake"

# 4. Verify and install SFML Developer packages
install_if_missing "libsfml-dev"

echo "========================================="
echo "Dependency Installation Verification"
echo "========================================="

# 5. Print Installed Versions
echo "Compiler Version:"
g++ --version | head -n 1
echo ""

echo "CMake Version:"
cmake --version | head -n 1
echo ""

echo "Make Version:"
make --version | head -n 1
echo ""

echo "SFML Development Files Details:"
if dpkg -s libsfml-dev >/dev/null 2>&1; then
    dpkg -s libsfml-dev | grep -E "(Package|Version|Status)"
else
    echo "Warning: libsfml-dev not found in dpkg query."
fi

echo ""
echo "========================================="
echo "Setup completed successfully! Exiting cleanly."
echo "========================================="
exit 0
