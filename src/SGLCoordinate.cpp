
#include "SGL/SGLCoordinate.h"

/*  */
static float _windowWidth;
static float _windowHeight;

SGLVOIDFUNC sgl::setWindowDimensions(float width, float height)
{
	_windowWidth = width;
	_windowHeight = height;
}

SGLFLOATFUNC sgl::getWindowWidth()
{
	return _windowWidth;
}

SGLFLOATFUNC sgl::getWindowHeight()
{
	return _windowHeight;
}

/* Util Function */
SGLVOIDFUNC sgl::util::pixelToNDC(float pixelX, float pixelY, float* ndcX, float* ndcY)
{
	*ndcX = ((pixelX / _windowWidth) - 0.5f) * 2.0f;
	*ndcY = ((pixelY / _windowHeight) - 0.5f) * 2.0f;
}


