#ifndef TRI_ANGLE_MESH
#define TRI_ANGLE_MESH

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

// This file loads basic .obj files and sets them up for opengl (must be triangulated)
struct vertex{
    float x,y,z;
    float r,g,b,a;
    float u,v;
};

namespace triangulated_mesh{
    void getVertexBufferAndIndeciesBufferFromObjectFile(std::string path, struct vertex*& vertexBuffer, int*& indecies);
}


#endif