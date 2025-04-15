#include <headers/opengl.hpp>
#include <string>

// implements the namepsace "state" from the included header

// static helper functions
static bool checkForNullPtr()
{
    if(opengl::state::ptr_FACE_BUFFER == nullptr) {return false;}
    if(opengl::state::ptr_INDECIES_BUFFER == nullptr) {return false;}

    if(opengl::state::ptr_VERTEX_BUFFER == nullptr) {return false;}
    if(opengl::state::ptr_FLOAT_BUFFER == nullptr) {return false;}
    return true;
}


// use this to create a Shader based on Path and write into a shader object
void opengl::state::createShader(Shader* shader, std::string vPath, std::string fPath)
{
    Shader shd(vPath, fPath);
    *shader = shd;
}


void opengl::state::loadObject(std::string path)
{
    triangulated_mesh::getVertexBufferAndFaceBufferFromObjectFile(
        path, 
        opengl::state::ptr_VERTEX_BUFFER, 
        opengl::state::ptr_FACE_BUFFER, 
        opengl::state::size_VERTEX_BUFFER, 
        opengl::state::size_FACE_BUFFER
    );
    opengl::utility::convertFacesToIndecies(
        opengl::state::size_FACE_BUFFER,
        opengl::state::ptr_FACE_BUFFER,
        opengl::state::ptr_INDECIES_BUFFER,
        opengl::state::size_INDECIES_BUFFER
    );
    opengl::utility::convertVerteciesToFloats(
        opengl::state::size_VERTEX_BUFFER,
        opengl::state::ptr_VERTEX_BUFFER,
        opengl::state::ptr_FLOAT_BUFFER,
        opengl::state::size_FLOAT_BUFFER
    );
}

void opengl::state::cleanPointers()
{
    delete[] opengl::state::ptr_FACE_BUFFER;
    delete[] opengl::state::ptr_INDECIES_BUFFER;
    delete[] opengl::state::ptr_VERTEX_BUFFER;
    delete[] opengl::state::ptr_FLOAT_BUFFER;
}

void opengl::state::setBuffersForSingleModellRendering()
{
    if(checkForNullPtr())
    {
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
}

/*
void opengl::state::setObjectForOpenGL()
{

}
*/