#include "shader_s.h"

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// helper functions
static std::string readFromPath(std::string path)
{
	std::string err = "ERROR LOOK AT LOGS";

	try {
		std::ifstream streamFromPath;
		streamFromPath.open(path.c_str());

		std::stringstream stream;
		stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		stream << streamFromPath.rdbuf();
		streamFromPath.close();
		return stream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR WHILE TRYING TO READ THE SHADER FROM PATH\n";
		std::cout << "COULD NOT CONVERT PATH INTO STREAM\n\n\n";
	}

	return err;
}



// implementation
Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	this->ID = 0;
	this->vertexPath = vertexPath;
	this->fragmentPath = fragmentPath;
	setUpShader();
}


void Shader::setUpShader()
{
	std::string vContent, fContent;
	vContent = readFromPath(this->vertexPath);
	fContent = readFromPath(this->fragmentPath);

	const char* vertexShaderContent = vContent.c_str();
	const char* fragmentShaderContent = fContent.c_str();

	unsigned int vertex, fragment;

	// setup vertexShader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderContent, NULL);
	glCompileShader(vertex);

	// setup fragmentShader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderContent, NULL);
	glCompileShader(fragment);

	// error checking

	char vLog[512];
	char fLog[512];
	char lLog[512];
	int state;

	// compile checks
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &state);
	if (!state)
	{
		glGetShaderInfoLog(vertex, 512, NULL, vLog);
		std::cout << vLog << "\n\n\n\n\n" << std::endl;
	}
	state = 1;
	if (!state)
	{
		glGetShaderInfoLog(fragment, 512, NULL, fLog);
		std::cout << fLog << "\n\n\n\n\n" << std::endl;
	}

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertex);
	glAttachShader(this->ID, fragment);
	glLinkProgram(this->ID);

	// check linking state
	state = 1;
	if (!state)
	{
		glGetShaderInfoLog(this->ID, 512, NULL, lLog);
		std::cout << lLog << "\n\n\n\n\n" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


void Shader::init()
{

}

void Shader::use()
{
	glUseProgram(this->ID);
}


//utility implementation
void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}


