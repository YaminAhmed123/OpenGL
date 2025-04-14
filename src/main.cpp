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



// Vertex positions (x, y, z)
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  // 0
     0.5f, -0.5f, -0.5f,  // 1
     0.5f,  0.5f, -0.5f,  // 2
    -0.5f,  0.5f, -0.5f,  // 3
    -0.5f, -0.5f,  0.5f,  // 4
     0.5f, -0.5f,  0.5f,  // 5
     0.5f,  0.5f,  0.5f,  // 6
    -0.5f,  0.5f,  0.5f   // 7
};

// Indices (12 triangles)
unsigned int indices[] = {
    // Back face
    0, 1, 2,
    2, 3, 0,
    // Front face
    4, 5, 6,
    6, 7, 4,
    // Left face
    4, 0, 3,
    3, 7, 4,
    // Right face
    1, 5, 6,
    6, 2, 1,
    // Bottom face
    4, 5, 1,
    1, 0, 4,
    // Top face
    3, 2, 6,
    6, 7, 3
};



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
    Shader ourShader;
    Shader shader;
    opengl::state::createShader(&shader, "shader/v2.glsl", "shader/f2.glsl");
    opengl::state::createShader(&ourShader, "shader/v2.glsl", "shader/f2.glsl");

    // set up vertex data (and buffer(s)) and configure vertex attributes

    opengl::state::loadObject("/home/yamin/repos/CPP/OpenGL/src/objectb2.obj");



    




    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, opengl::state::size_FLOAT_BUFFER * sizeof(float), &opengl::state::ptr_FLOAT_BUFFER[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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



    //matrix type shit to start making shit look like its 3D damn sleeek hehehe boi 
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));


    // the perpective
    float scr_width = static_cast<float>(SCR_WIDTH);
    float scr_height = static_cast<float>(SCR_HEIGHT);
    glm::mat4 proj;
    proj = glm::perspective(glm::radians(50.0f), (scr_width / scr_height), 0.1f, 100.0f);


    glm::mat4 model2 = glm::mat4(1.0f);
    model2 = glm::rotate(model2, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view2 = glm::mat4(1.0f);
    view2 = glm::translate(view2, glm::vec3(0.0f, 0.0f, -3.0f));


    // the perpective
    glm::mat4 proj2;
    proj2 = glm::perspective(glm::radians(50.0f), (scr_width / scr_height), 0.1f, 100.0f);









   

    
    
    // NOTE THIS PART OF THE CODES SETS THE UNIFORM MATRECIES IN THE SHADERS TO DO 3D TYPEEE SHIT
    ourShader.use();
    ourShader.setMat4("model", 1, GL_FALSE, glm::value_ptr(model));
    ourShader.setMat4("view", 1, GL_FALSE, glm::value_ptr(view));
    ourShader.setMat4("proj", 1, GL_FALSE, glm::value_ptr(proj));

    shader.use();
    shader.setMat4("model", 1, GL_FALSE, glm::value_ptr(model2));
    shader.setMat4("view", 1, GL_FALSE, glm::value_ptr(view2));
    shader.setMat4("proj", 1, GL_FALSE, glm::value_ptr(proj2));

    // rotate the ass cube lol
    
    model = glm::rotate(model, 1 * glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model2 = glm::rotate(model2, 1 * glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    float timeFirst, timeLast, deltaTime;
    timeFirst = glfwGetTime();

    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {


        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        timeLast = glfwGetTime();
        deltaTime = timeLast - timeFirst;

        model = glm::rotate(model, glm::radians(50.0f) * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
        model2 = glm::rotate(model2, glm::radians(50.0f) * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        

        // render container
        
        glBindVertexArray(VAO);
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
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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