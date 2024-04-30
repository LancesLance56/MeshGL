cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER C:/ProgramData/mingw64/mingw64/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/ProgramData/mingw64/mingw64/bin/g++.exe)


project(donut)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/gfx
)

# Add source files
set(SOURCES
    src/glad.c
    src/main.cpp
    src/gfx/window.cpp
    src/gfx/shader.cpp
    src/gfx/abo.cpp
    src/gfx/vao.cpp
    src/gfx/renderer.cpp
    src/gfx/texture.cpp
    src/gfx/camera.cpp
    src/handle_input.cpp
        src/mesh/perlin_mesh.cpp
        src/mesh/perlin_mesh.h
        src/mesh/perlin.cpp
)

# Add executable target
add_executable(donut ${SOURCES})

# Link GLFW library
target_link_libraries(donut ${CMAKE_SOURCE_DIR}/lib/libglfw3dll.a)
