#include <headers/opengl.hpp>

void opengl::camera::setOpenglCamera(Camera& cam)
{
    opengl::camera::camera = cam;
}

void opengl::camera::reCalculateMat4View()
{
    opengl::camera::camera.reCalculateViewMat4();
    opengl::camera::view = opengl::camera::camera.getViewMatrix();
}