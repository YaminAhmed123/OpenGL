#ifndef OPENGL_S
#define OPENGL_S

#include <headers/shader/shader_s.hpp>

/*
This header defines OpenGL as a state machine so in here
it is possible to find functions that set up the vertex buffers VBOS, VAOS, VEOS so they can be loaded. 
*/

namespace opengl {

    // a set of function to use opengl as a state machine
    namespace state
    {
        
        void createShader(Shader* shader, std::string vPath, std::string fPath); // will use a shader 
    }
}


#endif