#!/bin/bash

# ==============================================================================
# TIMBERMAN RUN SCRIPT
# ==============================================================================

set -euo pipefail

# Verify binary exists
if [ ! -f ./Timber ]; then
    echo "========================================="
    echo "ERROR: Timber executable not found!"
    echo "Please compile the project first by running:"
    echo "  bash build.sh"
    echo "========================================="
    exit 1
fi

echo "Running TimberMan..."
./Timber
