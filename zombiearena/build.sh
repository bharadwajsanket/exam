#!/bin/bash

echo "Building ZombieArena (SFML)..."

# Detect and add Homebrew paths on macOS if available
INCLUDE_FLAGS=""
LIBRARY_FLAGS=""

if [ -d "/opt/homebrew/include" ]; then
    INCLUDE_FLAGS="-I/opt/homebrew/include"
fi
if [ -d "/opt/homebrew/lib" ]; then
    LIBRARY_FLAGS="-L/opt/homebrew/lib"
fi

# Compile ZombieArena.cpp (which includes Player.cpp, zombie.cpp, bullet.cpp, and pickup.cpp)
if g++ $INCLUDE_FLAGS $LIBRARY_FLAGS ZombieArena.cpp -o ZombieArena -lsfml-graphics -lsfml-window -lsfml-system; then
    echo "==========================================="
    echo "Build SUCCESSFUL: Generated 'ZombieArena' binary"
    echo "==========================================="
else
    echo "==========================================="
    echo "Build FAILED: Please check if SFML is installed."
    echo "==========================================="
    exit 1
fi
