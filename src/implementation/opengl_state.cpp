#include <headers/opengl.hpp>
#include <string>

// implements the namepsace "state" from the included header



// use this to create a Shader based on Path and write into a shader object
void opengl::state::createShader(Shader* shader, std::string vPath, std::string fPath)
{
    Shader shd(vPath, fPath);
    *shader = shd;
}


