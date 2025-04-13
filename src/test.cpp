#include <iostream>
#include <string>
#include <fstream>

struct vertex{
    float x,y,z;
    float r,g,b,a;
    float u,v;
};

struct face{
    int first, second, third;
};

int countSubStringAmount(std::ifstream& stream, std::string substring)
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

void loadDataFromStreamForVertexBuffer(std::ifstream& stream, struct vertex* vertexBuffer)
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

void loadDataFromStreamForIndeciesBuffer(std::ifstream& stream, struct face* faceBuffer)
{
    int index = 0;
    std::string line;
    while(std::getline(stream, line))
    {
        if(line.rfind("f ", 0) == 0)
        {
            const char* CLine = line.c_str();
            sscanf(CLine, "f %d %d %d", &faceBuffer[index].first, &faceBuffer[index].second, &faceBuffer[index].third);
            ++index;
        } else{}
    }
}


int main()
{
    std::ifstream file("obj1.obj");
    std::ifstream file2("obj1.obj");

    int zahl = countSubStringAmount(file, "f ");

    struct face* face_ptr = new struct face[zahl];

    loadDataFromStreamForIndeciesBuffer(file2, face_ptr);

    for(int i = 0; i<zahl; i++)
    {
        std::cout << face_ptr[i].first << " " << face_ptr[i].second << " " << face_ptr[i].third << std::endl; 
    }

    delete[] face_ptr;
    

    return 0;
}