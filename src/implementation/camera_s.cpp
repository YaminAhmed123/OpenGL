#include <headers/camera/camera_s.hpp>

cam::Camera::Camera(glm::vec3 camera_postion, glm::vec3 camera_direction)
{
	this->camera_position = camera_position;
	this->camera_view_direction = camera_view_direction;
}

cam::Camera::~Camera()
{

}
