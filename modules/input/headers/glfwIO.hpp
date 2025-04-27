#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <opengl/headers/opengl.hpp>
#include <timing/headers/time.hpp>

// This header declares a set of functions used to Handle I/O coming from the user
namespace IO{

    // inline double xpos = 0;
    // inline double ypos = 0;
    inline bool walking_mode = false;
    inline float sensetivity = 0.05f;
    inline float lastX = 300.0f;
    inline float lastY = 400.0f;
    inline bool firstMouse = true;



    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    void processInput(GLFWwindow* window);

    // callback functions
    void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
}