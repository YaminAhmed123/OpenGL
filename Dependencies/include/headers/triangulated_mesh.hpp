#ifndef TRI_ANGLE_MESH
#define TRI_ANGLE_MESH

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

// This file loads basic .obj files and sets them up for opengl (must be triangulated)
#pragma pack(push, 1)
struct vertex{
    float x,y,z;
    //float r,g,b,a;
    //float u,v;
};
#pragma pack(pop)

struct face{
    int first, second, third;
};

namespace triangulated_mesh{
    void getVertexBufferAndFaceBufferFromObjectFile(std::string path, struct vertex*& vertexBuffer, struct face*& indecies, int& v_SIZE, int& f_SIZE);
}


#endif