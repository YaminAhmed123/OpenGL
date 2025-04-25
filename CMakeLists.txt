cmake_minimum_required(VERSION 3.10)
project(RenderEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/include/imgui
)

# fetches all source files and stores their path in the SOURCE variable
set(SOURCES
    src/main.cpp
    src/glad.c
    src/implementation/shader_s.cpp
    src/implementation/camera_s.cpp
    src/implementation/glfwIO.cpp
    src/implementation/gui.cpp
    src/implementation/opengl_camera.cpp
    src/implementation/opengl_state.cpp
    src/implementation/opengl_utility.cpp
    src/implementation/triangulated_mesh.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_impl_glfw.cpp
    src/imgui/imgui_impl_opengl3.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui.cpp
    src/imgui/imgui_demo.cpp
)

add_library(RenderEngineObject OBJECT ${SOURCES})

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Code for Linux
    # set compiler flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -march=native")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -march=native")

    # now here comes the part where its gets OS specific
    add_executable(RenderEngineExecutable
        $<TARGET_OBJECTS:RenderEngineObject>
    )

    # Link statically built GLFW and required system libraries
    target_link_libraries(RenderEngineExecutable
        ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/lib/libglfw3.a
    )
    
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Code for Windows
    add_executable(RenderEngineExecutable
        $<TARGET_OBJECTS:RenderEngineObject>
    )

    target_link_libraries(RenderEngineExecutable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/lib/glfw3.lib)
    
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()
