
#include "SGL/Util/PerspectiveCamera.h"

#include "SGL/Math/MathUtil.h"

using namespace sgl;

PerspectiveCamera::PerspectiveCamera(float fov, float viewportWidth, float viewportHeight) : Camera(viewportWidth, viewportHeight),
	_fov(fov)
{
	calculateProjectionMatrix();
}

void PerspectiveCamera::calculateProjectionMatrix(void)
{
	float aspect = _viewportWidth / _viewportHeight;

	float tanHalfFov = tan(DEG_TO_RAD(_fov) / 2.0f);

	_proj[0][0] = 1.0f / (aspect * tanHalfFov);
	_proj[1][1] = 1.0f / (tanHalfFov);
	_proj[2][2] = -((_zFar + _zNear) / (_zFar - _zNear));
	_proj[2][3] = -1.0f;
	_proj[3][2] = -(2.0f * _zFar * _zNear) / (_zFar - _zNear);
}