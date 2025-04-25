# OpenGL based Render Engine **alpha stage** [![Static Badge](https://img.shields.io/badge/GLFW-blue)](https://github.com/glfw/glfw)   [![Static Badge](https://img.shields.io/badge/ImGui-lightgreen)](https://github.com/ocornut/imgui)  [![Static Badge](https://img.shields.io/badge/OpenGL-darkgreen)](https://www.opengl.org/)
This project is an [OpenGL](https://www.khronos.org/) based render engine with linux and windows support the goal is to be feature rich and cross compilable.  




## Features
- Model loading from obj files that can be created in Blender
- Software based Ray Tracer that runs on all GPUs aiming for biggest compatibility
- basic shaders that can be used for lightning
- loading third party **GLSL** shaders to customize the experience
- using Cmake as a cross build tool for windows and linux for easy usage

### Links I used for learning and building
- [Learn OpenGL](https://learnopengl.com/) from my point of view a good resource to learn OpenGL and get a grasp of the concepts.
- [Scratch Pixel](https://www.scratchapixel.com/index.html) explains a lot about **CG** in genereal and can be usful if you focus on specific aspects.
- [Cmake](https://cmake.org/) CMake is the chosen build system for managing cross-platform builds.
- [imGUI](https://github.com/ocornut/imgui) this is a selfcontained library for creating GUIs.

## How to compile ?    [![Static Badge](https://img.shields.io/badge/MSVC-darkblue)](https://learn.microsoft.com/de-de/cpp/build/reference/compiler-options?view=msvc-170)   [![Static Badge](https://img.shields.io/badge/GCC-purple)](https://gcc.gnu.org/)   [![Static Badge](https://img.shields.io/badge/CMake-darkred)](https://cmake.org/)

### Linux
- clone the repo after that create a dir called build if there is no build directory.
- then go type from the build dir the command cmake ..
- after that type in the command make.
- and last add the shader and images directories there where the executable file is located at
- Note this section will be reimplemented in future.

### NOTICE
- read me not done yet
- most features are coming soon
