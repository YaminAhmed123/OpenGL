#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>


struct gui_state
{
    /*
    The data inside this stuct conatins the GUI data
    These will be used for statemanagement
    It is highly reccomended to only have one instance of this struct 
    if more things are needed they can be added in this header 
    */

    bool WIRE_FRAME_STATE;
    bool SHADER_STATE;
    bool APPLICATION_END_STATE;
};

namespace gui {
    void setGUIforStart(struct gui_state* GUI);
    void setUpGUI(GLFWwindow* window);
    void setUICode(struct gui_state* GUI, GLFWwindow* win);
    void setFrame();
    void setRender();
    void cleanUp();
}