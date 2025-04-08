#include <headers/gui.hpp>


// These function here are used to help with GUI logic
static void HANDLE_FOR_WIRE_FRAME(struct gui_state* GUI)
{
    if(GUI->WIRE_FRAME_STATE)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        GUI->WIRE_FRAME_STATE = false;
    }
    else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        GUI->WIRE_FRAME_STATE = true;
    }
}

static void HANDLE_FOR_SHADER(struct gui_state* GUI)
{
    if(GUI->SHADER_STATE)
    {
        GUI->SHADER_STATE = false;
    }
    else{
        GUI->SHADER_STATE = true;
    }
}









void gui::setGUIforStart(struct gui_state *GUI)
{
    GUI->APPLICATION_END_STATE = false;
    GUI->SHADER_STATE = false;
    GUI->WIRE_FRAME_STATE = false;
}

void gui::setUpGUI(GLFWwindow* window)
{
    // init IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();
}

void gui::setUICode(struct gui_state* GUI, GLFWwindow* win)
{
    ImGui::Begin("Controls");
    ImGui::Text("Test from UI Code");
    if(ImGui::Button("toggle wireframe"))
    {
        HANDLE_FOR_WIRE_FRAME(GUI);
    }
    if(ImGui::Button("toggle shader"))
    {
        HANDLE_FOR_SHADER(GUI);
    }
    if(ImGui::Button("close application"))
    {
        glfwSetWindowShouldClose(win, true);
    }
    ImGui::End();
}

void gui::setFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void gui::setRender()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void gui::cleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();    
}