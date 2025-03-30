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

	/*
		DISCLAIMER !!!

		Note that any utility function here must be used in such a way that OpenGL know 
		which shader you mean. So if you have multiple shader objects and obj1 is set as the used program
		and you then call obj2 and set the uniform that uniform would be applied to obj1 since OpenGL uses this currently
		so you should call obj2.use() and then call the uniform functiosn to set its values etc.
	*/

	void setFloat(std::string name, float value) const;
	void setInt(std::string name, int value) const;
	void setVector3(std::string name, float x, float y, float z) const;
	void setVector2(std::string name, float x, float y) const;
	void setMat4(std::string name,unsigned int count, GLboolean state, GLfloat *value_ptr) const;

};

#endif
