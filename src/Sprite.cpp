
#include "SGL/Sprite.h"

using namespace sgl;

Sprite::Sprite(float x, float y, float w, float h, Texture* tex)
{
	_pos = new glm::vec2(x, y);
	_dim = new glm::vec2(w, h);

	_texture = tex;

	_updateQuad = true;
}

void Sprite::flip(bool h, bool v)
{
	// flip on the vertical axis
	if (v)
	{
		// swap top left with top right, and bottom left with bottom right
		// to vertically flip the region on the quad

		// tmp vars
		glm::vec2 tl = _region.topLeft;
		glm::vec2 bl = _region.bottomLeft;

		// swap
		_region.topLeft = _region.topRight;
		_region.bottomLeft = _region.bottomRight;
		_region.topRight = tl;
		_region.bottomRight = bl;
	}

	// flip on the horizontal axis
	if (h)
	{
		// swap the top left with bottom left and top right with bottom right
		// to horizontally flip the region on the quad

		// tmp vars
		glm::vec2 bl = _region.bottomLeft;
		glm::vec2 br = _region.bottomRight;

		// swap
		_region.bottomLeft = _region.topLeft;
		_region.bottomRight = _region.topRight;
		_region.topLeft = bl;
		_region.topRight = br;
	}
}

glm::vec2& Sprite::getPosition()
{
	_updateQuad = true;
	return *_pos;
}

float Sprite::getWidth()
{
	return _dim->x;
}

float Sprite::getHeight()
{
	return _dim->y;
}

glm::vec2& Sprite::getDimesions()
{
	return (*_dim);
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
	_dim->x = w;
	_dim->y = h;
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
		sgl::util::makeQuad(_quad, (*_pos).x, (*_pos).y, _dim->x, _dim->y);
		_updateQuad = false;
	}

	return _quad;
}

Sprite::~Sprite()
{
	delete _pos;
	delete _dim;
}
