cmake_minimum_required(VERSION 3.10)
project(SurfaceOptimizer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Platform-specific FreeGLUT configuration
if(WIN32)
    set(FREEGLUT_DIR "C:/freeglut" CACHE PATH "FreeGLUT installation directory")
    include_directories(${FREEGLUT_DIR}/include)
    link_directories(${FREEGLUT_DIR}/lib/x64)
else()
    # Linux/Mac: Use system-installed FreeGLUT
    find_package(GLUT REQUIRED)
    find_package(OpenGL REQUIRED)
    include_directories(${GLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
endif()

# Include directories
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR})

# Common source files
set(COMMON_SOURCES
    src/Point3D.cpp
    src/Surface.cpp
    src/Optimizer.cpp
    src/Visualizer.cpp
)

# Equation parser sources
set(EQUATION_SOURCES
    EquationParser.cpp
    GUIManager.cpp
)

# Main executable with equation GUI
add_executable(optimizer 
    ${COMMON_SOURCES}
    ${EQUATION_SOURCES}
    main_equation_gui.cpp
)

# Original demo executable
add_executable(optimizer_demo 
    ${COMMON_SOURCES}
    main.cpp
)

# Link libraries
if(WIN32)
    target_link_libraries(optimizer freeglut opengl32 glu32)
    target_link_libraries(optimizer_demo freeglut opengl32 glu32)
    
    # Copy freeglut DLL
    add_custom_command(TARGET optimizer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${FREEGLUT_DIR}/bin/x64/freeglut.dll"
        $<TARGET_FILE_DIR:optimizer>
        COMMENT "Copying freeglut.dll"
    )
else()
    target_link_libraries(optimizer ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} m)
    target_link_libraries(optimizer_demo ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} m)
endif()

# Installation
install(TARGETS optimizer optimizer_demo
    RUNTIME DESTINATION bin
)

# Print configuration
message(STATUS "=================================")
message(STATUS "3D Surface Optimizer Configuration")
message(STATUS "=================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Main executable: optimizer")
message(STATUS "Demo executable: optimizer_demo")
if(WIN32)
    message(STATUS "FreeGLUT directory: ${FREEGLUT_DIR}")
endif()
message(STATUS "=================================")