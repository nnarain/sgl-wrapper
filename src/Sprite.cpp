
#include "SGL/Sprite.h"

using namespace sgl;

Sprite::Sprite(float x, float y, float w, float h, Texture* tex)
{
	_pos = new glm::vec2(x, y);
	_width = w;
	_height = h;
	_texture = tex;

	_updateQuad = true;
}

glm::vec2 Sprite::getPosition()
{
	return *_pos;
}

float Sprite::getWidth()
{
	return _width;
}

float Sprite::getHeight()
{
	return _height;
}

Texture* Sprite::getTexture()
{
	return _texture;
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
	_width = w;
	_height = h;
	_updateQuad = true;
}

void Sprite::setPosition(glm::vec2 pos)
{
	setPosition(pos.x, pos.y);
}

void Sprite::setPosition(float x, float y)
{
	(*_pos).x = x;
	(*_pos).y = y;
	_updateQuad = true;
}

Texture::TextureRegion& Sprite::getTextureRegion()
{
	return _region;
}

Quad& Sprite::getQuad()
{
	if (_updateQuad)
	{
		sgl::util::makeQuad(_quad, (*_pos).x, (*_pos).y, _width, _height);
		_updateQuad = false;
	}

	return _quad;
}

Sprite::~Sprite()
{
}
