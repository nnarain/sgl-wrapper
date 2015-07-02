
#include "SGL/Util/Context.h"

using namespace sgl;

Vector2 Context::_viewPort = Vector2(0, 0);

void Context::clear(BufferBits bits)
{
	glClear(static_cast<GLbitfield>(bits));
}

void Context::setViewPortDimension(float w, float h)
{
	_viewPort.x = w;
	_viewPort.y = h;
}

Vector2 Context::getViewPortDimensions(void)
{
	return _viewPort;
}

float Context::getViewPortWidth(void)
{
	return _viewPort.x;
}

float Context::getViewPortHeight(void)
{
	return _viewPort.y;
}

float Context::getScreenAspectRatio(void)
{
	return _viewPort.x / _viewPort.y;
}