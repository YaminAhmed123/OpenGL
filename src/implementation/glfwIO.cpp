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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        opengl::camera::camera.camera_position.y += 5.0f* deltatime::delta_time;
        opengl::camera::camera.reCalculateViewMat4();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        opengl::camera::camera.camera_position.y += -5.0f* deltatime::delta_time;
        opengl::camera::camera.reCalculateViewMat4();
    }

    // This is to enable/disable V-SYNC (causes the stuttering issues on linux) 
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        glfwSwapInterval(0);
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        glfwSwapInterval(1);
    }


    // TEMPORARY FIX ADDED KIND OFF
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void IO::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void IO::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (IO::firstMouse)
    {
        IO::lastX = xpos;
        IO::lastY = ypos;
        IO::firstMouse = false;
    }

    // calculate the offset of the mouse postions for each axis
    float offset_x = static_cast<float>(xpos - IO::lastX);
    float offset_y = static_cast<float>(IO::lastY - ypos);
    offset_x *= IO::sensetivity;
    offset_y *= IO::sensetivity;


    // update lastY and lastX
    IO::lastX = xpos;
    IO::lastY = ypos;

    opengl::camera::camera.yaw += offset_x;
    opengl::camera::camera.pitch += offset_y;
    if (opengl::camera::camera.pitch > 89.0f){ opengl::camera::camera.pitch = 89.0f; }
    if (opengl::camera::camera.pitch < -89.0f) { opengl::camera::camera.pitch = -89.0f; }

    opengl::camera::camera.reCalculateViewMat4();
}