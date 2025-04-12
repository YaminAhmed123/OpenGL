#include <iostream>
#include <string>
#include <fstream>

struct vertex{
    float x,y,z;
    float r,g,b,a;
    float u,v;
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

void loadDataFromStreamForIndeciesBuffer(std::ifstream& stream, int* indeciesBuffer)
{
    int index = 0;
    std::string line;
    while(std::getline(stream, line))
    {
        if(line.rfind("f ", 0) == 0)
        {
            const char* CLine = line.c_str();
            sscanf(CLine, "f %d %d %d", &indeciesBuffer[index], &indeciesBuffer[index+1], &indeciesBuffer[index+2]);
            ++index;
            ++index;
            ++index;
        } else{}
    }
}


int main()
{
    std::ifstream file("obj1.obj");
    std::ifstream file2("obj1.obj");

    int zahl = countSubStringAmount(file, "f ");
    std::cout << zahl << std::endl;
    int* array = new int[zahl];

    loadDataFromStreamForIndeciesBuffer(file2, array);

    for(int i = 0; i<zahl; i++)
    {
        int c = i+1;
        int cc = i+2;
        std::cout << array[i] << " " << array[c] << " " << array[cc] << std::endl;
    }

    return 0;
}