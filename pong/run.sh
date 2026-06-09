#!/bin/bash

if [ -f "./Pong" ]; then
    echo "Starting Pong..."
    # S-05-score/main.cpp expects fonts inside a relative 'font/' directory.
    # We change directory to S-05-score/ so the paths resolve correctly.
    cd S-05-score
    ../Pong
else
    echo "Error: Pong binary not found."
    echo "Please run the build script first:"
    echo "  bash build.sh"
    exit 1
fi
