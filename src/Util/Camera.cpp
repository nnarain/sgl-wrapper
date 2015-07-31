
#include "SGL/Util/Camera.h"

// Math
#include "SGL/Math/MathUtil.h"
#include "SGL/Math/Vector4.h"

#include <GL/glew.h>

using namespace sgl;

Camera::Camera()
{
}

Camera::Camera(float viewportWidth, float viewportHeight) :
	_viewportWidth(viewportWidth),
	_viewportHeight(viewportHeight),
	_zNear(0.1f),
	_zFar(100.0f),
	_up(0,1,0),
	_dirty(true)
{
	updateViewPort();
}

void Camera::update()
{
	// calculate the new view matrix if required

	if (_dirty)
	{
		calculateViewMatrix();

		_dirty = false;
	}
}

void Camera::calculateViewMatrix(void)
{
	// calculate eye space basis vectors

	// eye space z-axis
	Vector3f z = (_target - _pos).normalize();

	// eye space x-axis
	Vector3f x = Vector3f(z).cross(_up).normalize();

	// eye space y-axis
	Vector3f y = Vector3f(x).cross(z).normalize();

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

	_view[3][3] = 1;
}

void Camera::lookAt(const Vector3f& v)
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

	// normalized device coordinates
	float x = ((viewportX / _viewportWidth) - 0.5f) * 2.0f;
	float y = ((viewportY / _viewportHeight) - 0.5f) * 2.0f;

	// near far vectors
	Vector4f near(x, y, -1.0f, 1.0f);
	Vector4f far(x, y, 0.0f, 1.0f);

	// inverse projection
	Matrix4 invProj(_proj);
	invProj.invert();

	// inverse view
	Matrix4 invView(_view);
	invView.invert();

	// unproject and unview the coordinates to get world space
	Vector4f csStart = invProj * near;
	csStart /= csStart.w;
	Vector4f wsStart = invView * csStart;
	wsStart /= wsStart.w;

	Vector4f csEnd = invProj * far;
	csEnd /= csEnd.w;
	Vector4f wsEnd = invView * csEnd;
	wsEnd /= wsEnd.w;

	Vector4f tmp = (wsEnd - wsStart).normalize();
	Vector3f direction = Vector3f(tmp.x, tmp.y, tmp.z);

	return Ray(Vector3f(wsStart.x, wsStart.y, wsStart.z), direction);
}

void Camera::updateViewPort()
{
	glViewport(0, 0, _viewportWidth, _viewportHeight);
}

Matrix4 Camera::combined()
{
	return _proj * _view;
}

const Matrix4& Camera::projection() const
{
	return _proj;
}


const Matrix4& Camera::view() const
{
	return _view;
}

void Camera::setPosition(const Vector3f& vec)
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

Vector3f& Camera::getPosition()
{
	return _pos;
}

Vector3f Camera::getDirection()
{
	return (_target - _pos).normalize();
}

const Vector3f& Camera::getUpVector() const
{
	return _up;
}

void Camera::setUpVector(const Vector3f &up)
{
	_up.x = up.x;
	_up.y = up.y;
	_up.z = up.z;
}

const Vector3f& Camera::getTarget() const
{
	return _target;
}

float Camera::getViewPortWidth(void) const
{
	return _viewportWidth;
}


float Camera::getViewPortHeight(void) const
{
	return _viewportHeight;
}

/**
	Get the cameras far clipping distance
*/
float Camera::getFarClipping() const
{
	return _zFar;
}

/**
	Get the cameras near clipping distance
*/
float Camera::getNearClipping() const
{
	return _zNear;
}

Camera::~Camera()
{

}
