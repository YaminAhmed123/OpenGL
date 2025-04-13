#ifndef OPENGL_S
#define OPENGL_S

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <headers/shader/shader_s.hpp>
#include <headers/triangulated_mesh.hpp>
#include <string>

/*
This header defines OpenGL as a state machine so in here
it is possible to find functions that set up the vertex buffers VBOS, VAOS, VEOS so they can be loaded. 
*/

namespace opengl {

    //defines a set of function usefull for geometry handling
    namespace utility
    {
        void convertFacesToIndecies(int faceBufferSize, struct face* faceBuffer, int*& ptr_INDECIES, int& indeciesSize);   // Note that the size of indecies buffer is just 3xfaceBufferSize
        void convertVerteciesToFloats(int vBufferS, struct vertex* vBuffer, float*& ptr_floats, int& floatSize);
    }

    // a set of function to use opengl as a state machine
    namespace state
    {
        inline int size_VERTEX_BUFFER = 0;
        inline int size_FACE_BUFFER = 0;
        inline int size_INDECIES_BUFFER = 0;
        inline int size_FLOAT_BUFFER = 0;
        inline struct vertex* ptr_VERTEX_BUFFER = nullptr;       // CAUTION THESE PTR HAVE MEMORY ALLOCATED ON HEAP DELETE AFTER USAGE NEEDED
        inline struct face* ptr_FACE_BUFFER = nullptr;           // CAUTION THESE PTR HAVE MEMORY ALLOCATED ON HEAP DELETE AFTER USAGE NEEDED
        inline int* ptr_INDECIES_BUFFER = nullptr;               // CAUTION THESE PTR HAVE MEMORY ALLOCATED ON HEAP DELETE AFTER USAGE NEEDED   
        inline float* ptr_FLOAT_BUFFER = nullptr;                // CAUTION THESE PTR HAVE MEMORY ALLOCATED ON HEAP DELETE AFTER USAGE NEEDED
        
        void createShader(Shader* shader, std::string vPath, std::string fPath); // creates a shader and writes it to the specified adress (maybe that function is useless)
        void loadObject(std::string path);
        // void setObjectForOpenGL();
        void cleanPointers();                   // Can only be called after loadObject was called

    }
}


#endif