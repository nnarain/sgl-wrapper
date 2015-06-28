
#include "SGL/Util/OrthographicCamera.h"

using namespace sgl;

OrthographicCamera::OrthographicCamera(float viewportWidth, float viewportHeight, Vector2 x, Vector2 y, Vector2 z) :
	Camera(viewportWidth, viewportHeight),
	_left(x.x),
	_right(x.y),
	_top(y.x),
	_bottom(y.y),
	_near(z.x),
	_far(z.y)
{
	calculateProjectionMatrix();
}

void OrthographicCamera::calculateProjectionMatrix()
{
	// x axis
	_proj[0][0] = 2.0f / (_right - _left);

	// y axis
	_proj[1][1] = 2.0f / (_top - _bottom);

	// z axis
	_proj[2][2] = -2.0f / (_far - _near);

	//
	_proj[3][0] = -(_right + _left) / (_right - _left);
	_proj[3][1] = -(_top + _bottom) / (_top - _bottom);
	_proj[3][2] = -(_far + _near) / (_far - _near);
	_proj[3][3] = 1;
}
