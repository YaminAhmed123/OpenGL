#ifndef SHADER_S
#define SHADER_S

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {
private:
	unsigned int ID;
	std::string vertexPath;
	std::string fragmentPath;

	void setUpShader();

public:
	Shader(std::string vertexPath, std::string fragmentPath);
	void use();

	//utility functions for uniform types
	void setFloat(std::string name, float value);
	void setInt(std::string name, int value);
	void setVector3(std::string name, float x, float y, float z);

};

#endif
