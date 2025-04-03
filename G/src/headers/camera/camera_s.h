#ifndef CAMERA_S
#define CAMERA_S

#include <glm/glm.hpp>

namespace cam 
{
	/*
	*	This header defines a set of functions and a class to implement a simulated camera 
	*	in OpenGL this header will be very simple and not optimised
	*	therfore consider using a different implementation in future instead of relying on this one
	*	with this claimer its up to you to make it better
	*/

	class Camera
	{
	public:
		Camera(glm::vec3 camera_postion, glm::vec3 camera_direction);
		~Camera();

	private:
		glm::vec3 camera_position;
		glm::vec3 camera_view_direction;
	};

}
#endif