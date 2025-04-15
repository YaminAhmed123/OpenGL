#include <headers/gui.hpp>
#include <headers/opengl.hpp>
#include <headers/ui/portable-file-dialogs.h>


// local vars const buffers
static char buffer[512];

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

static void HANDLE_FOR_MESHLOADING(std::string path)
{
    opengl::state::cleanPointers();     // NOTE THAT THE APPLICATION MUST LOAD A DEFAULT OBJECT AT BEGINNING
    opengl::state::loadObject(path);

    // set up Opengl State
    glDeleteVertexArrays(1, &opengl::state::VAO);
    glDeleteBuffers(1, &opengl::state::VBO);
    glDeleteBuffers(1, &opengl::state::EBO);

    // set up new buffers and settings

    glGenVertexArrays(1, &opengl::state::VAO);
    glGenBuffers(1, &opengl::state::VBO);
    glGenBuffers(1, &opengl::state::EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(opengl::state::VAO);

    glBindBuffer(GL_ARRAY_BUFFER, opengl::state::VBO);
    glBufferData(GL_ARRAY_BUFFER, opengl::state::size_FLOAT_BUFFER * sizeof(float), &opengl::state::ptr_FLOAT_BUFFER[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl::state::EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, opengl::state::size_INDECIES_BUFFER * sizeof(int), &opengl::state::ptr_INDECIES_BUFFER[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
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
    if(ImGui::Button("load mesh object"))
    {
        pfd::open_file fileDialog(
            "Choose an object file",         // Dialog title
            ".",                   // Default path (current directory)
            { "All Files", "*.obj" }   // Filter
        );
    
        std::vector<std::string> result = fileDialog.result();
    
        if (!result.empty())
        {
            std::string selectedPath = result[0];
            HANDLE_FOR_MESHLOADING(selectedPath);
        }
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