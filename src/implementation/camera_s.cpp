#include <headers/camera/camera_s.hpp>


// Camera Constructors
Camera::Camera(){}      // no args

Camera::Camera(glm::vec3 pos)
{
    this->camera_position = pos;
}

Camera::Camera(glm::vec3 pos, glm::vec3 front)
{
    this->camera_position = pos;
    this->camera_front = front;
}

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
{
    this->camera_position = pos;
    this->camera_front = front;
    this->camera_up = up;
}



// implementation of camera functions

glm::mat4 Camera::getViewMatrix(){ return this->view; }
glm::vec3 Camera::getCamera_Front(){ return this->camera_front; }
glm::vec3 Camera::getCamera_Pos(){ return this->camera_position; }
glm::vec3 Camera::getCamera_Up(){ return this->camera_up; }

void Camera::setCameraPosition(glm::vec3 pos)
{
    this->camera_position = pos;
}

void Camera::setCameraFront(glm::vec3 front)
{
    this->camera_front = front;
}

void Camera::setCameraUP(glm::vec3 up)
{
    this->camera_up = up;
}

void Camera::reCalculateViewMat4()
{
	this->view = glm::lookAt(this->camera_position, this->camera_front + this->camera_position, this->camera_up);
}

