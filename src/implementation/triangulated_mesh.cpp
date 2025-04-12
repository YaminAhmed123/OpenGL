#include <headers/triangulated_mesh.hpp>
#include <fstream>
#include <stdio.h>

static int countSubStringAmount(std::ifstream& stream, std::string substring)
{
    int count = 0;
    std::string line;

    while(std::getline(stream, line))
    {
        if(line.find(substring) != std::string::npos)
        {
            ++count;
        }
    }

    return count;
}

static void loadDataFromStreamForVertexBuffer(std::ifstream& stream, struct vertex* vertexBuffer)
{
    int index = 0;
    std::string line;
    while(std::getline(stream, line))
    {
        if(line.rfind("v ", 0) == 0)
        {
            const char* CLine = line.c_str();
            sscanf(CLine, "v %f %f %f", &vertexBuffer[index].x, &vertexBuffer[index].y, &vertexBuffer[index].z);
            ++index;
        } else{}
    }
}


static void loadDataFromStreamForIndeciesBuffer(std::ifstream& stream, int* indeciesBuffer)
{
    int index = 0;
    std::string line;
    while(std::getline(stream, line))
    {
        if(line.rfind("f ", 0) == 0)
        {
            const char* CLine = line.c_str();
            sscanf(CLine, "f %d %d %d", &indeciesBuffer[index], &indeciesBuffer[index+1], &indeciesBuffer[index+2]);
            index+=3;
        } else{}
    }
}


void triangulated_mesh::getVertexBufferAndIndeciesBufferFromObjectFile(std::string path, struct vertex*& vertexBuffer, int*& indecies)
{
    int vAmount;
    int fAmount;

    {
        std::ifstream file(path);
        vAmount = countSubStringAmount(file, "v ");
    }
    {
        std::ifstream file(path);
        fAmount = countSubStringAmount(file, "f ");
    }

    //create Vertex Buffer
    vertexBuffer = new struct vertex[vAmount];
    indecies = new int[fAmount];

    {
        std::ifstream file(path);
        loadDataFromStreamForVertexBuffer(file, vertexBuffer);
    }


    
    


}