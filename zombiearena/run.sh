#!/bin/bash

if [ -f "./ZombieArena" ]; then
    echo "Starting ZombieArena..."
    ./ZombieArena
else
    echo "Run: bash build.sh"
    exit 1
fi
