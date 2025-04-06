#include <headers/shader/shader_s.h>

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
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &state);
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
	glGetShaderiv(this->ID, GL_LINK_STATUS, &state);
	if (!state)
	{
		glGetShaderInfoLog(this->ID, 512, NULL, lLog);
		std::cout << lLog << "\n\n\n\n\n" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}



void Shader::use() const
{
	glUseProgram(this->ID);
}


//utility implementation

static int ifUniformFound(unsigned int location, std::string name)
{
	if (location == -1) { 
	 	std::cout << "There is no uniform found with the Name: " << name << std::endl;
		return -1;
	}
	return 1;
}



void Shader::setFloat(std::string name, float value) const
{
	const char* nameC = name.c_str();
	unsigned int location = glGetUniformLocation(this->ID, nameC);
	if (ifUniformFound(location, name)) {
		glUniform1f(location, value);
	}
}

void Shader::setInt(std::string name, int value) const
{
	const char* nameC = name.c_str();
	unsigned int location = glGetUniformLocation(this->ID, nameC);
	if (ifUniformFound(location, name)) {
		glUniform1i(location, value);
	}
}

void Shader::setVector3(std::string name, float x, float y , float z) const 
{
	const char* nameC = name.c_str();
	unsigned int location = glGetUniformLocation(this->ID, nameC);
	if (ifUniformFound(location, name)) {
		glUniform3f(location, x,y,z);
	}
}

void Shader::setVector2(std::string name, float x, float y) const 
{
	const char* nameC = name.c_str();
	unsigned int location = glGetUniformLocation(this->ID, nameC);
	if(ifUniformFound(location, name)){
		glUniform2f(location, x, y);
	}
}

void Shader::setMat4(std::string name, unsigned int count, GLboolean state, GLfloat* value_ptr) const
{
	const char* nameC = name.c_str();
	unsigned int location = glGetUniformLocation(this->ID, nameC);
	if(ifUniformFound(location, name))
	{
		glUniformMatrix4fv(location, count, state, value_ptr);
	}
}
