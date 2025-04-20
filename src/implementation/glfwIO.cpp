#include <headers/glfwIO.hpp>

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void IO::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){ glfwSetWindowShouldClose(window, true); }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        opengl::camera::camera.camera_position.z += -5.0f * deltatime::delta_time; 
        opengl::camera::camera.reCalculateViewMat4();
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        opengl::camera::camera.camera_position.x += -5.0f * deltatime::delta_time;
        opengl::camera::camera.reCalculateViewMat4();
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        opengl::camera::camera.camera_position.z += 5.0f * deltatime::delta_time;
        opengl::camera::camera.reCalculateViewMat4();
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        opengl::camera::camera.camera_position.x += 5.0f * deltatime::delta_time;
        opengl::camera::camera.reCalculateViewMat4();
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE))
    {
        opengl::camera::camera.camera_position.y += 5.0f* deltatime::delta_time;
        opengl::camera::camera.reCalculateViewMat4();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
    {
        opengl::camera::camera.camera_position.y += -5.0f* deltatime::delta_time;
        opengl::camera::camera.reCalculateViewMat4();
    }
}

void IO::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}