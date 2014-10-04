
#include "Camera.h"
#include <glm/gtx/transform.hpp>

using namespace sgl;

Camera::Camera()
{
}

Camera::Camera(float fov, float aspectRatio)
{
	proj = glm::perspective(fov, aspectRatio, 0.1f, 100.0f);
}

void Camera::update()
{
	view = glm::lookAt(glm::vec3(pos.x, pos.y, pos.z), glm::vec3(target.x, target.y, target.z), glm::vec3(0, 1, 0));
}

void Camera::translate(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
}

void Camera::translate(Vector3f vec)
{
	translate(vec.x, vec.y, vec.z);
}

void Camera::lookAt(Vector3f v)
{
	lookAt(v.x, v.y, v.z);
}

void Camera::lookAt(float x, float y, float z)
{
	target.x = x;
	target.y = y;
	target.z = z;
}

glm::mat4 Camera::combined()
{
	return (proj) * (view);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return proj;
}

glm::mat4 Camera::getViewMatrix()
{
	return view;
}

void Camera::setPosition(Vector3f vec)
{
	setPosition(vec.x, vec.y, vec.z);
}

void Camera::setPosition(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

Camera::~Camera()
{
}
