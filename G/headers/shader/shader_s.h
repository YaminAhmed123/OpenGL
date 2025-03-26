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
	void init();

	//utility functions for uniform types
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

};

#endif
