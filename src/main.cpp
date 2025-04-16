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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
static bool stateOfShader = false;
// global GUI state
struct gui_state GUI;


int main()
{

    Camera camera = Camera(glm::vec3(1.0f, 1.0f, 1.0f));



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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
    model2 = glm::rotate(model2, 1 * glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    float timeFirst, timeLast, deltaTime;
    timeFirst = glfwGetTime();

    
    // render loop
    // -----------
    int view = 1;
    std::cout << view2[3][2] << std::endl;
    shader.use();
    while (!glfwWindowShouldClose(window))
    {


        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        timeLast = glfwGetTime();
        deltaTime = timeLast - timeFirst;

        
        model2 = glm::rotate(model2, glm::radians(60.0f) * 2 * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
        
        if(view == 1)
        {
            view2 = glm::translate(view2, glm::vec3(0.0f, 0.0f,deltaTime * -1.0f * 4.5f));
            if(view2[3][2] <= -15.0f)
            {
                view = -1;
            }
        }
        if(view == -1){
            view2 = glm::translate(view2, glm::vec3(0.0f, 0.0f,deltaTime * 1.0f * 4.5f));
            if(view2[3][2] >= -3.5f)
            {
                view = 1;
            }
        }

        shader.setMat4("model", 1, GL_FALSE, glm::value_ptr(model2));
        shader.setMat4("view", 1, GL_FALSE, glm::value_ptr(view2));
        shader.setMat4("proj", 1, GL_FALSE, glm::value_ptr(proj2));

        // input
        // -----
        processInput(window);

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
        timeFirst = timeLast;

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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        stateOfShader = true;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        stateOfShader = false;
    }

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}