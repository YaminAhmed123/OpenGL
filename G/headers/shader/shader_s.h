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
	void use() const;

	//utility functions for uniform types
	void setFloat(std::string name, float value) const;
	void setInt(std::string name, int value) const;
	void setVector3(std::string name, float x, float y, float z) const;
	void setVector2(std::string name, float x, float y) const;

};

#endif
