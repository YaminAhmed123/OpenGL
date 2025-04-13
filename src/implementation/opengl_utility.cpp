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