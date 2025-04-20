#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <headers/opengl.hpp>
#include <headers/time.hpp>

// This header declares a set of functions used to Handle I/O coming from the user
namespace IO{
    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    void processInput(GLFWwindow* window);

    // framebuffer callback function
    void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
}