#include <headers/opengl.hpp>
#include <string>

// implements the namepsace "state" from the included header

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

/*
void opengl::state::setObjectForOpenGL()
{

}
*/