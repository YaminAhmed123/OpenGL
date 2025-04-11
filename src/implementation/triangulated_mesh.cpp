#include <headers/triangulated_mesh.hpp>
#include <fstream>


static int countSubStringAmount(std::ifstream& stream, std::string substring)
{
    int count = 0;
    std::string line;

    while(std::getline(stream, line))
    {
        if(line.find(substring)!= std::string::npos)
        {
            ++count;
        }
    }

    return count;
}


void triangulated_mesh::getVertexBufferAndIndeciesBufferFromObjectFile(std::string path, struct vertex* vertexBuffer, int* indecies)
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
    struct vertex* vBuffer = static_cast<struct vertex*>(malloc(sizeof(struct vertex)* vAmount));
    int* fBuffer = static_cast<int*>(malloc(sizeof(int)*fAmount));
    
    


}