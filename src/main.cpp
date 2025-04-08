#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <headers/img_loading/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <headers/shader/shader_s.h>
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
    Shader ourShader("shader/vertexShader.glsl", "shader/fragmentShader.glsl");
    Shader shader("shader/v.glsl", "shader/f.glsl");



    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // color attribute
    /*
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    */


    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);


    
    
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


    //______________________________________________________________________________________________


    glm::mat4 model2 = glm::mat4(1.0f);
    model2 = glm::rotate(model2, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view2 = glm::mat4(1.0f);
    view2 = glm::translate(view2, glm::vec3(0.0f, 0.0f, -3.0f));


    // the perpective
    glm::mat4 proj2;
    proj2 = glm::perspective(glm::radians(50.0f), (scr_width / scr_height), 0.1f, 100.0f);









    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("images/stone.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    
    
    // NOT THIS PART OF THE CODES SETS THE UNIFORM MATRECIES IN THE SHADERS TO DO 3D TYPEEE SHIT
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



        // select which shader to use
        if (GUI.SHADER_STATE) {
            shader.use();
            float time = static_cast<float>(glfwGetTime());
            float valX = glm::sin(time);
            float valY = glm::cos(time);
            float valZ = -glm::sin(time);
            shader.setVector3("lol", valX, valY, valZ);
            shader.setMat4("model", 1, GL_FALSE, glm::value_ptr(model2));
            shader.setMat4("view", 1, GL_FALSE, glm::value_ptr(view2));
            shader.setMat4("proj", 1, GL_FALSE, glm::value_ptr(proj2));
        }
        else {
            ourShader.use();
            float time = static_cast<float>(glfwGetTime());
            float valX = glm::sin(time);
            float valY = glm::cos(time);
            float valZ = -glm::sin(time);
            ourShader.setVector3("lol", valX, valY, valZ);
            ourShader.use();
            ourShader.setMat4("model", 1, GL_FALSE, glm::value_ptr(model));
            ourShader.setMat4("view", 1, GL_FALSE, glm::value_ptr(view));
            ourShader.setMat4("proj", 1, GL_FALSE, glm::value_ptr(proj));
        }

        

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

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