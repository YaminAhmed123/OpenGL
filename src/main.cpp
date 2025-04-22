#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <headers/img_loading/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <headers/shader/shader_s.hpp>
#include <headers/opengl.hpp>
#include <iostream>
#include <headers/camera/camera_s.hpp>

//include imgui stuff
#include <headers/gui.hpp>
#include <headers/time.hpp>
#include <headers/glfwIO.hpp>

 
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
static bool stateOfShader = false;
// global GUI state
struct gui_state GUI;

void yes(){ std::cout << "shit got called\n";}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, IO::framebuffer_size_callback);

    if (glfwRawMouseMotionSupported()){ glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE); }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, IO::cursor_position_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Setup GUI
    gui::setGUIforStart(&GUI);
    gui::setUpGUI(window);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader shader;
    opengl::state::createShader(&shader, "shader/v2.glsl", "shader/f2.glsl");

    // set up vertex data (and buffer(s)) and configure vertex attributes

    opengl::state::loadObject("object/object.obj");
    opengl::state::setBuffersForSingleModellRendering();


    //matrix type shit to start making shit look like its 3D damn sleeek hehehe boi 
    glm::mat4 model2 = glm::mat4(1.0f);

    glm::mat4 view2 = glm::mat4(1.0f);
    view2 = glm::translate(view2, glm::vec3(0.0f, 0.0f, -4.0f));


    // the perpective
    float scr_width, scr_height;
    scr_width = SCR_WIDTH;
    scr_height = SCR_HEIGHT;
    glm::mat4 proj2;
    proj2 = glm::perspective(glm::radians(40.0f), (scr_width / scr_height), 0.1f, 100.0f);

    
    
    // NOTE THIS PART OF THE CODES SETS THE UNIFORM MATRECIES IN THE SHADERS TO DO 3D TYPEEE SHIT

    shader.use();
    shader.setMat4("model", 1, GL_FALSE, glm::value_ptr(model2));
    shader.setMat4("view", 1, GL_FALSE, glm::value_ptr(view2));
    shader.setMat4("proj", 1, GL_FALSE, glm::value_ptr(proj2));

    // rotate the ass cube lol
    model2 = glm::rotate(model2, 1 * glm::radians(40.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    
    deltatime::first = glfwGetTime();
    shader.use();
    while (!glfwWindowShouldClose(window))
    {


        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        deltatime::last = glfwGetTime();
        deltatime::delta_time = deltatime::last - deltatime::first;

        shader.setMat4("model", 1, GL_FALSE, glm::value_ptr(model2));
        shader.setMat4("view", 1, GL_FALSE, glm::value_ptr(opengl::camera::camera.view));
        shader.setMat4("proj", 1, GL_FALSE, glm::value_ptr(proj2));


        model2 = glm::rotate(model2, deltatime::delta_time * glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        // input
        // -----
        IO::processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        

        // render container
        
        glBindVertexArray(opengl::state::VAO);
        glDrawElements(GL_TRIANGLES, opengl::state::size_INDECIES_BUFFER, GL_UNSIGNED_INT, 0);

        // (Your code calls glfwPollEvents())
        // ...


        // Start the Dear ImGui frame
        gui::setFrame();
        gui::setUICode(&GUI, window);
        gui::setRender();



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        deltatime::first = deltatime::last;
    }

    opengl::state::cleanPointers();
    gui::cleanUp();

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &opengl::state::VAO);
    glDeleteBuffers(1, &opengl::state::VBO);
    glDeleteBuffers(1, &opengl::state::EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}