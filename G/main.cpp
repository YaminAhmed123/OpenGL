// this branch will be used to learn texture loading

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "headers/shader_s.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "headers/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

    // build and compile our shader program
    // ------------------------------------
    const char* vPath = "vertexShader.glsl";
    const char* fPath = "fragmentShader.glsl";
    Shader ourShader(vPath, fPath); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f,	    0.0f, 0.0f, 1.0f,
		0.0f,  0.5f, 0.0f ,     1.0f, 0.0f, 0.0f,
    };

    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();
        glBindVertexArray(VAO);

        // modify uniforms
        float timeValue = glfwGetTime();
        float redValue = (cos(timeValue) / 2.0f) + 0.489f;
		ourShader.setFloat("offset1", redValue);

		float timeValue2 = glfwGetTime();
		float greenValue = (-sin(timeValue2) / 2.0f) + 0.489f;
		ourShader.setFloat("offset2", greenValue);

		float timeValue3 = glfwGetTime();
		float blueValue = (-cos(timeValue3) / 2.0f) + 0.489f;
		ourShader.setFloat("offset3", blueValue);

        glDrawArrays(GL_TRIANGLES, 0, 12);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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
    {
        std::cout << "Terminate Application\n";
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window,GLFW_KEY_1) == GLFW_PRESS)
    {
		std::cout << "Wireframe mode" << std::endl; 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if(glfwGetKey(window,GLFW_KEY_2) == GLFW_PRESS)
    {
		std::cout << "Fill mode" << std::endl;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // add the back color to keys
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        std::cout << "Background color set to black" << std::endl;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        std::cout << "Background color set to white" << std::endl;
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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