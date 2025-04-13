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
    std::ifstream file("obj2.obj");
    std::ifstream file2("obj2.obj");


    int zahl = countSubStringAmount(file, "f ");

    struct face* face_ptr = new struct face[zahl];

    loadDataFromStreamForIndeciesBuffer(file2, face_ptr);

    for(int i = 0; i<zahl; i++)
    {
        std::cout << face_ptr[i].first << " " << face_ptr[i].second << " " << face_ptr[i].third << std::endl; 
    }

    delete[] face_ptr;

    std::ifstream file3("obj2.obj");
    std::ifstream file4("obj2.obj");

    int zahl2 = countSubStringAmount(file3, "v ");
    struct vertex* vBuffer = new struct vertex[zahl2];

    loadDataFromStreamForVertexBuffer(file4, vBuffer);

    for(int i = 0; i< zahl2; i++)
    {
        std::cout << vBuffer[i].x << " " << vBuffer[i].y << " " << vBuffer[i].z << std::endl;
    }
    

    return 0;
}