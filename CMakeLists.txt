cmake_minimum_required(VERSION 3.10)
project(SurfaceOptimizer)

set(CMAKE_CXX_STANDARD 17)

# Find OpenGL and GLUT (optional)
find_package(OpenGL)
find_package(GLUT)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/Point3D.cpp
    src/Surface.cpp
    src/Optimizer.cpp
)

# Main executable (console version)
add_executable(optimizer main.cpp ${SOURCES})

# If OpenGL found, create visualizer version
if(OPENGL_FOUND AND GLUT_FOUND)
    add_executable(optimizer_visual 
        main_visual.cpp 
        src/Visualizer.cpp 
        ${SOURCES})
    target_link_libraries(optimizer_visual ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
endif()