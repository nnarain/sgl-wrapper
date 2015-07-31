
#include "SGL/Graphics/Sprite.h"
#include "SGL/Util/Context.h"

#include <algorithm>

using namespace sgl;

Sprite::Sprite(float x, float y, float w, float h, Texture* tex) :
	_pos(x, y),
	_dim(w, h),
	_color(1,1,1,1),
	_texture(tex),
	_updateQuad(true)
{
}

void Sprite::flip(bool h, bool v)
{
	// flip on the vertical axis
	if (v)
	{
		// swap top left with top right, and bottom left with bottom right
		// to vertically flip the region on the quad

		std::swap(_region.topLeft, _region.topRight);
		std::swap(_region.bottomLeft, _region.bottomRight);
	}

	// flip on the horizontal axis
	if (h)
	{
		// swap the top left with bottom left and top right with bottom right
		// to horizontally flip the region on the quad

		std::swap(_region.bottomLeft, _region.topLeft);
		std::swap(_region.bottomRight, _region.topRight);
	}
}

Vector2f& Sprite::getPosition()
{
	_updateQuad = true;
	return _pos;
}

float Sprite::getWidth()
{
	return _dim.x;
}

float Sprite::getHeight()
{
	return _dim.y;
}

Vector2f& Sprite::getDimesions()
{
	return _dim;
}

Texture* Sprite::getTexture()
{
	return _texture;
}

void Sprite::setTexture(Texture *t)
{
	_texture = t;
}

void Sprite::setTextureRegion(Texture::TextureRegion region)
{
	_region = region;
}

void Sprite::setTextureRegion(float x, float y, float w, float h)
{
	_region = _texture->region(x, y, w, h);
}

void Sprite::setDimensions(float w, float h)
{
	_dim.x = w;
	_dim.y = h;
	_updateQuad = true;
}

void Sprite::setPosition(Vector2f pos)
{
	setPosition(pos.x, pos.y);
}

void Sprite::setPosition(float x, float y)
{
	_pos.x = x;
	_pos.y = y;
	_updateQuad = true;
}

Texture::TextureRegion& Sprite::getTextureRegion()
{
	return _region;
}

Rect& Sprite::getQuad()
{
	if (_updateQuad)
	{
		//sgl::util::makeQuad(_quad, _pos.x, _pos.y, _dim.x, _dim.y);

//		_quad.bottomLeft  = Context::pixelToNDC(_pos.x, _pos.y);
//		_quad.topLeft     = Context::pixelToNDC(_pos.x, _pos.y + _dim.y);
//		_quad.topRight    = Context::pixelToNDC(_pos.x + _dim.x, _pos.x + _dim.y);
//		_quad.bottomRight = Context::pixelToNDC(_pos.x + _dim.x, _pos.y);
//
		_quad.x      = _pos.x;
		_quad.y      = _pos.y;
		_quad.width  = _dim.x;
		_quad.height = _dim.y;

		_updateQuad = false;
	}

	return _quad;
}

void Sprite::setColor(const ColorRGBA32f& c)
{
	_color = c;
}

ColorRGBA32f& Sprite::getColor()
{
	return _color;
}

Sprite::~Sprite()
{

}
