#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class Camera{

	private:
	std::string camera_name;

	public:
	glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 3.3f);	// default settings
	glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);		// default settings
	glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);			// default settings
	glm::vec3 camera_direction = glm::vec3(0.0f, 0.0f, -1.0f);  // default settings
	glm::mat4 view = glm::lookAt(this->camera_position, this->camera_front + this->camera_position, this->camera_up);

	// yaw and pitch values
	float yaw = 0.0f;											// theses vals get manipulated by glfwIO.hpp
	float pitch = 0.0f;											// theses vals get manipulated by glfwIO.hpp
	
	Camera();													// no args constructor	select default settings
	Camera(glm::vec3 pos);										// some overloads
	Camera(glm::vec3 pos, glm::vec3 front);						// some overloads
	Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up);		// some overloads

	glm::mat4 getViewMatrix();
	glm::vec3 getCamera_Pos();
	glm::vec3 getCamera_Front();
	glm::vec3 getCamera_Up();

	void setCameraPosition(glm::vec3 pos);
	void setCameraFront(glm::vec3 front);
	void setCameraUP(glm::vec3 up);

	// A set of functions used to modify the camera values
	void reCalculateViewMat4();	// warning this function calls setCameraFront() !!!
	void calcDirectionVec3();
	void setCameraFront();		// warning this functions calls calcDirectionVec3() !!!

	void shiftCameraPosByDirectionVec3AndIgnoreY_Axis(float sensetivity, bool POS_OR_NEG, float yaw);		// Note that this function uses a normalized version of the direction vecotr !!!
																											// The POS_OR_NEG param is there tos set in which direction it should be shifted +/-
	void shiftCameraPosByTheCrossProductOfDirection(float sensetivity, bool POS_OR_NEG);
};

#endif