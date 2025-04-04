cmake_minimum_required(VERSION 3.20)
project(OpenGL)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories (replace with your actual include path)
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/include)

# Add library directories (replace with your actual library path)
link_directories(${CMAKE_SOURCE_DIR}/Dependencies/lib)

# Collect source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Create the executable
add_executable(OpenGL ${SRC_FILES})

# Link GLFW library
target_link_libraries(OpenGL PRIVATE libglfw3.a)
