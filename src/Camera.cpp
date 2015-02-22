
#include "SGL/Camera.h"

// Math
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <algorithm>

using namespace sgl;

Camera::Camera()
{
}

Camera::Camera(float fov, float viewportWidth, float viewportHeight) :
	_fov(fov),
	_nearClipping(0.1f),
	_farClipping(100.0f),
	_viewportWidth(viewportWidth),
	_viewportHeight(viewportHeight),
	_proj(new glm::mat4),
	_view(new glm::mat4),
	_target(new glm::vec3),
	_up(new glm::vec3(0,1,0)),
	_right(new glm::vec3),
	_look(new glm::vec3)
{
	float aspectRatio = _viewportWidth / _viewportHeight;
	*_proj = glm::perspective(fov, aspectRatio, _nearClipping, _farClipping);
}

Camera::Camera(const Camera& that) : Camera::Camera(that._fov, that._viewportWidth, that._viewportHeight)
{
}

void Camera::update()
{
	// calculate the view matrix
	*_view = glm::lookAt(*_pos, *_target, *_up);

	// calculate look direction vector
	*_look = glm::normalize(*_target - (*_pos));

	// calculate the right vector
	glm::vec3 crs = glm::cross(glm::vec3((*_look).x, 0, (*_look).z), *_up);
	*_right = glm::normalize(crs);
}

void Camera::lookAt(glm::vec3 v)
{
	lookAt(v.x, v.y, v.z);
}

void Camera::lookAt(float x, float y, float z)
{
	(*_target).x = x;
	(*_target).y = y;
	(*_target).z = z;
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
	glm::mat4 invProj = glm::inverse(*_proj);
	glm::mat4 invView = glm::inverse(*_view);

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
	return (*_proj) * (*_view);
}

glm::mat4 Camera::projection()
{
	return *_proj;
}

glm::mat4 Camera::view()
{
	return *_view;
}

glm::vec3 Camera::direction() const
{
	return glm::normalize((*_target) - (*_pos));
}

glm::mat4 Camera::transform()
{
	return glm::translate(*_pos);
}

void Camera::setPosition(glm::vec3 vec)
{
	setPosition(vec.x, vec.y, vec.z);
}

void Camera::setPosition(float x, float y, float z)
{
	(*_pos).x = x;
	(*_pos).y = y;
	(*_pos).z = z;
}

glm::vec3 Camera::getPosition() const
{
	return (*_pos);
}

glm::vec3 Camera::getUpVector() const
{
	return *_up;
}

void Camera::setUpVector(glm::vec3 up)
{
	*_up = up;
}

glm::vec3 Camera::getLookDirection() const
{
	return *_look;
}

glm::vec3 Camera::getRightDirection() const
{
	return *_right;
}

void sgl::swap(Camera& first, Camera& second)
{
	using std::swap;

	swap(first._fov, second._fov);
	swap(first._pos, second._pos);
	swap(first._target, second._target);
	swap(first._proj, second._proj);
	swap(first._view, second._view);
	swap(first._farClipping, second._farClipping);
	swap(first._nearClipping, second._nearClipping);
	swap(first._up, second._up);
	swap(first._look, second._look);
	swap(first._right, second._right);
}

Camera& Camera::operator=(Camera that)
{
	swap(*this, that);
	return *this;
}

Camera::~Camera()
{
	delete _pos;
	delete _target;
	delete _up;
	delete _look;
	delete _right;
	delete _view;
	delete _proj;
}
