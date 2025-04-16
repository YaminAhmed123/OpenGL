#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{

	private:
	int ID;
	
	glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 3.3f);	// default settings
	glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);		// default settings
	glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);			// default settings

	glm::mat4 view = glm::lookAt(this->camera_position, this->camera_front, this->camera_up);



	public:
	Camera();													// no args constructor	select default settings
	Camera(glm::vec3 pos);										// some overloads
	Camera(glm::vec3 pos, glm::vec3 front);						// some overloads
	Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up);		// some overloads

	glm::mat4 getViewMatrix();
	glm::vec3 getCamera_Pos();
	glm::vec3 getCamera_Front();
	glm::vec3 getCamera_Up();

	

	// A set of functions used to modify the camera values
	void reCalculateViewMat4();
};

#endif