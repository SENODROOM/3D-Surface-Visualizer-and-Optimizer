cmake_minimum_required(VERSION 3.10)
project(SurfaceOptimizer)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/Point3D.cpp
    src/Surface.cpp
    src/Optimizer.cpp
)

# Main executable (console version only)
add_executable(optimizer main.cpp ${SOURCES})