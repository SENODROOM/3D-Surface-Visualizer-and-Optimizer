#!/bin/bash

set -e  # Exit on error

echo "========================================="
echo "  3D Surface Optimizer - Build Script"
echo "========================================="
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check for required tools
echo "Checking prerequisites..."

if ! command -v cmake &> /dev/null; then
    echo -e "${RED}ERROR: CMake not found!${NC}"
    echo "Please install CMake: sudo apt-get install cmake"
    exit 1
fi

if ! command -v g++ &> /dev/null; then
    echo -e "${RED}ERROR: g++ not found!${NC}"
    echo "Please install g++: sudo apt-get install build-essential"
    exit 1
fi

echo -e "${GREEN}✓ CMake found${NC}"
echo -e "${GREEN}✓ g++ found${NC}"

# Check for OpenGL/GLUT
if ! ldconfig -p | grep -q libglut; then
    echo -e "${YELLOW}WARNING: FreeGLUT not found!${NC}"
    echo "Install with: sudo apt-get install freeglut3-dev"
    read -p "Continue anyway? (y/n) " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
else
    echo -e "${GREEN}✓ FreeGLUT found${NC}"
fi

echo ""

# Create build directory
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
else
    echo "Build directory exists"
    read -p "Clean build directory? (y/n) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        rm -rf build/*
        echo "Build directory cleaned"
    fi
fi

cd build

# Run CMake
echo ""
echo "Running CMake configuration..."
if cmake .. -DCMAKE_BUILD_TYPE=Release; then
    echo -e "${GREEN}✓ CMake configuration successful${NC}"
else
    echo -e "${RED}✗ CMake configuration failed!${NC}"
    exit 1
fi

# Build
echo ""
echo "Compiling project..."
if cmake --build . --config Release; then
    echo -e "${GREEN}✓ Compilation successful${NC}"
else
    echo -e "${RED}✗ Compilation failed!${NC}"
    exit 1
fi

# Check executables
echo ""
echo "Checking build artifacts..."
if [ -f "release/optimizer" ]; then
    echo -e "${GREEN}✓ optimizer executable created${NC}"
    chmod +x optimizer
else
    echo -e "${RED}✗ optimizer executable not found!${NC}"
    exit 1
fi

if [ -f "optimizer_demo" ]; then
    echo -e "${GREEN}✓ optimizer_demo executable created${NC}"
    chmod +x optimizer_demo
else
    echo -e "${YELLOW}⚠ optimizer_demo executable not found${NC}"
fi

# Success message
echo ""
echo "========================================="
echo -e "${GREEN}  BUILD COMPLETE!${NC}"
echo "========================================="
echo ""
echo "Created executables:"
echo "  ./build/optimizer       - Main program with equation GUI"
echo "  ./build/optimizer_demo  - Original demo version"
echo ""
echo "To run:"
echo "  cd build && ./optimizer"
echo ""
echo "Controls in 3D view:"
echo "  W/S - Rotate up/down"
echo "  A/D - Rotate left/right"
echo "  +/- - Zoom in/out"
echo "  R   - Reset view"
echo "  ESC - Exit"
echo ""