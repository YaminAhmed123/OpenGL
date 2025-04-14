#include <headers/opengl.hpp>

void opengl::utility::convertFacesToIndecies(int faceBufferSize, struct face* faceBuffer, int*& ptr_INDECIES, int& indeciesSize)
{
    ptr_INDECIES = new int[faceBufferSize*3];

    int indexForPtr = 0;
    for(int i = 0; i<faceBufferSize; i++)
    {
        ptr_INDECIES[indexForPtr] = faceBuffer[i].first;
        ++indexForPtr;
        ptr_INDECIES[indexForPtr] = faceBuffer[i].second;
        ++indexForPtr;
        ptr_INDECIES[indexForPtr] = faceBuffer[i].third;
        ++indexForPtr;
    }
    indeciesSize = faceBufferSize*3;
}

void opengl::utility::convertVerteciesToFloats(int vBufferS, struct vertex* vBuffer, float*& ptr_floats, int& floatSize)
{
    ptr_floats = new float[vBufferS*3];

    int indexForPtr = 0;
    for(int i = 0; i<vBufferS; i++)
    {
        ptr_floats[indexForPtr] = vBuffer[i].x;
        ++indexForPtr;
        ptr_floats[indexForPtr] = vBuffer[i].y;
        ++indexForPtr;
        ptr_floats[indexForPtr] = vBuffer[i].z;
        ++indexForPtr;
    }
    floatSize = vBufferS*3;

    // Fix indexing since OpenGL uses 0 based indexing
    for(int i = 0; i<opengl::state::size_INDECIES_BUFFER; i++)
    {
        opengl::state::ptr_INDECIES_BUFFER[i] = opengl::state::ptr_INDECIES_BUFFER[i]-1; 
    }
}