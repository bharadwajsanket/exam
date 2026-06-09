#!/bin/bash

# ==============================================================================
# TIMBERMAN BUILD SCRIPT
# Target: Ubuntu Linux / macOS (g++ with SFML)
# ==============================================================================

set -euo pipefail

echo "========================================="
echo "Building TimberMan..."
echo "========================================="

# 1. Detect compiler
if ! command -v g++ &> /dev/null; then
    echo "ERROR: g++ compiler not found!"
    echo "Please run 'bash setup.sh' first to install required tools."
    exit 1
fi

echo "Compiler detected: $(g++ --version | head -n 1)"

# 2. Setup SFML library paths for macOS if needed
EXTRA_FLAGS=""
if [[ "$(uname -s)" == "Darwin" ]]; then
    if [ -d "/opt/homebrew/include" ]; then
        EXTRA_FLAGS="-I/opt/homebrew/include -L/opt/homebrew/lib"
    elif [ -d "/usr/local/include" ]; then
        EXTRA_FLAGS="-I/usr/local/include -L/usr/local/lib"
    fi
fi

# 3. Compile Timber.cpp
echo "Compiling Timber.cpp into binary 'Timber'..."
if g++ Timber.cpp -o Timber $EXTRA_FLAGS -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio; then
    echo "========================================="
    echo "SUCCESS: TimberMan built successfully!"
    echo "Executable generated: ./Timber"
    echo "========================================="
else
    echo "========================================="
    echo "ERROR: Compilation failed!"
    echo "Ensure libsfml-dev is installed and all asset folders exist."
    echo "========================================="
    exit 1
fi
