
#include "SGL/Util/Camera.h"

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
	_up(0,1,0),
	_dirty(true)
{
	float aspectRatio = _viewportWidth / _viewportHeight;
	//*_proj = glm::perspective(fov, aspectRatio, _nearClipping, _farClipping);
}

void Camera::update()
{
	if (_dirty)
	{
		// calculate the camera view matrix

		// eye space z-axis
		Vector3 z = (_target - _pos).normalize();

		// eye space x-axis
		Vector3 x = Vector3(z).cross(_up).normalize();

		// eye space y-axis
		Vector3 y = Vector3(x).cross(z);

		// store results in the view matrix

		/*
			| right.x   up.x   forward.x   position.x |
			| right.y   up.y   forward.y   position.x |
			| right.z   up.z   forward.z   position.x |
			|   0        0         0           1      |

			Rows and columns are transposed
		*/

		// right
		_view[0][0] = x.x;
		_view[1][0] = x.y;
		_view[2][0] = x.z;
		_view[3][0] = x.dot(_pos) * -1;

		// up
		_view[0][1] = y.x;
		_view[1][1] = y.y;
		_view[2][1] = y.z;
		_view[3][1] = y.dot(_pos) * -1;

		// forward
		_view[0][2] = -z.x;
		_view[1][2] = -z.y;
		_view[2][2] = -z.z;
		_view[3][2] = z.dot(_pos);

		// position
		//_view[0][3] = x.dot(_pos) * -1;;
		//_view[1][3] = y.dot(_pos) * -1;;
		//_view[2][3] = z.dot(_pos);
		_view[3][3] = 1;

		_dirty = false;
	}
}

void Camera::lookAt(const Vector3& v)
{
	lookAt(v.x, v.y, v.z);
}

void Camera::lookAt(float x, float y, float z)
{
	_target.x = x;
	_target.y = y;
	_target.z = z;

	_dirty = true;
}

Ray Camera::pickRay(float viewportX, float viewportY)
{
/*
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
*/
	return Ray();
}

Matrix4 Camera::combined()
{
	return Matrix4();
}

const Matrix4& Camera::projection() const
{
	return _proj;
}


const Matrix4& Camera::view() const
{
	return _view;
}


const Matrix4& Camera::transform() const
{
	return Matrix4();
}

void Camera::setPosition(const Vector3& vec)
{
	setPosition(vec.x, vec.y, vec.z);
}

void Camera::setPosition(float x, float y, float z)
{
	_pos.x = x;
	_pos.y = y;
	_pos.z = z;

	_dirty = true;
}

const Vector3& Camera::getPosition() const
{
	return _pos;
}

const Vector3& Camera::getUpVector() const
{
	return _up;
}

void Camera::setUpVector(const Vector3 &up)
{
	_up.x = up.x;
	_up.y = up.y;
	_up.z = up.z;
}

Vector3& Camera::getTarget() const
{
	return Vector3();
}

Camera::~Camera()
{

}
