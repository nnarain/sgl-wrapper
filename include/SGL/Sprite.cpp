
#include "Sprite.h"

using namespace sgl;

Sprite::Sprite(float x, float y, float w, float h, Texture* tex)
{
	_pos = glm::vec2(x, y);
	_width = w;
	_height = h;
	_texture = tex;
}

glm::vec2 Sprite::getPosition()
{
	return _pos;
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

Texture::TextureRegion* Sprite::getTextureRegion()
{
	return &_region;
}

Sprite::~Sprite()
{
}
