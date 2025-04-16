#ifndef CAMERA_S
#define CAMERA_S

#include <glm/glm.hpp>

class Camera{

	private:
	int ID;
	
	glm::vec3 camera_position;


	public:
	Camera(glm::vec3 pos);
};

#endif