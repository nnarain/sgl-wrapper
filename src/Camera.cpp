
#include "Camera.h"
#include <glm/gtx/transform.hpp>

using namespace sgl;

Camera::Camera()
{
}

Camera::Camera(float fov, float viewportWidth, float viewportHeight)
{
	_nearClipping = 0.1f;
	_farClipping = 100.0f;

	_viewportWidth = viewportWidth;
	_viewportHeight = viewportHeight;

	float aspectRatio = viewportWidth / viewportHeight;
	_proj = glm::perspective(fov, aspectRatio, _nearClipping, _farClipping);
}

void Camera::update()
{
	_view = glm::lookAt(_pos, _target, glm::vec3(0, 1, 0));
}

void Camera::translate(float x, float y, float z)
{
	_pos.x += x;
	_pos.y += y;
	_pos.z += z;
}

void Camera::translate(glm::vec3 vec)
{
	translate(vec.x, vec.y, vec.z);
}

void Camera::lookAt(glm::vec3 v)
{
	lookAt(v.x, v.y, v.z);
}

void Camera::lookAt(float x, float y, float z)
{
	_target.x = x;
	_target.y = y;
	_target.z = z;
}

Ray Camera::pickRay(float viewportX, float viewportY)
{
	// normalized device coordinates
	float x = ((viewportX / _viewportWidth) - 0.5f) * 2.0f;
	float y = ((viewportY / _viewportHeight) - 0.5f) * 2.0f;

	// near far vectors
	glm::vec4 near = glm::vec4(x, y, -1.0f, 1.0f);
	glm::vec4 far = glm::vec4(x, y, 0.0f, 1.0f);

	// inverse matrices
	glm::mat4 invProj = glm::inverse(_proj);
	glm::mat4 invView = glm::inverse(_view);

	// unproject and unview the coordinates to get world space
	glm::vec4 csStart = invProj * near;
	csStart /= csStart.w;
	glm::vec4 wsStart = invView * csStart;
	wsStart /= wsStart.w;

	glm::vec4 csEnd = invProj * far;
	csEnd /= csEnd.w;
	glm::vec4 wsEnd = invView * csEnd;
	wsEnd /= wsEnd.w;

	glm::vec3 direction = glm::normalize(glm::vec3(wsEnd - wsStart));

	Ray ray;
	ray.origin = glm::vec3(wsStart);
	ray.direction = direction;

	return ray;
}

glm::mat4 Camera::combined()
{
	return (_proj)* (_view);
}

glm::mat4 Camera::projection()
{
	return _proj;
}

glm::mat4 Camera::view()
{
	return _view;
}

glm::vec3 Camera::direction() const
{
	return glm::normalize(_target - _pos);
}

void Camera::setPosition(glm::vec3 vec)
{
	setPosition(vec.x, vec.y, vec.z);
}

void Camera::setPosition(float x, float y, float z)
{
	_pos.x = x;
	_pos.y = y;
	_pos.z = z;
}

Camera::~Camera()
{
}
