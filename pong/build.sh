#!/bin/bash

echo "Building Pong (SFML)..."

# Detect and add Homebrew paths on macOS if available
INCLUDE_FLAGS=""
LIBRARY_FLAGS=""

if [ -d "/opt/homebrew/include" ]; then
    INCLUDE_FLAGS="-I/opt/homebrew/include"
fi
if [ -d "/opt/homebrew/lib" ]; then
    LIBRARY_FLAGS="-L/opt/homebrew/lib"
fi

# Compile final stage S-05-score/main.cpp
if g++ $INCLUDE_FLAGS $LIBRARY_FLAGS S-05-score/main.cpp -o Pong -lsfml-graphics -lsfml-window -lsfml-system; then
    echo "==========================================="
    echo "Build SUCCESSFUL: Generated 'Pong' binary"
    echo "==========================================="
else
    echo "==========================================="
    echo "Build FAILED: Please check if SFML is installed."
    echo "==========================================="
    exit 1
fi
