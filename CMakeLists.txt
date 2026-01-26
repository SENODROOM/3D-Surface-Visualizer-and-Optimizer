cmake_minimum_required(VERSION 3.10)
project(SurfaceOptimizer)

set(CMAKE_CXX_STANDARD 17)

# Set freeglut directory
set(FREEGLUT_DIR "C:/freeglut")

# Include directories
include_directories(include)
include_directories(${FREEGLUT_DIR}/include)

# Link directories
link_directories(${FREEGLUT_DIR}/lib)

# Source files for visualization version
set(SOURCES
    src/Point3D.cpp
    src/Surface.cpp
    src/Optimizer.cpp
    src/Visualizer.cpp
    main.cpp
)

# Main executable with visualization
add_executable(optimizer ${SOURCES})

# Link OpenGL and freeglut libraries
target_link_libraries(optimizer freeglut opengl32 glu32)