
#include "SGL/Texture.h"

#include <memory>
#include <algorithm>

using namespace sgl;

Texture::Texture(Target target, int width, int height, GLint internalFormat, GLenum format) :
	_width(width),
	_height(height),
	_internalFormat(internalFormat),
	_format(format),
	_isBound(false)
{
	create();
	setTarget(target);
}

void Texture::create()
{
	glGenTextures(1, &_id);
}

void Texture::data(char* pixels)
{
	data(_target, pixels);
}

void Texture::data(GLuint target, char* pixels)
{
	assert(_isBound && "Texture has not been bound");

	glTexImage2D(target, 0, _internalFormat, _width, _height, 0, _format, GL_UNSIGNED_BYTE, pixels);
}

void Texture::bind(GLuint target)
{
	glActiveTexture(target);
	glBindTexture(_target, _id);

	_isBound = true;
}

void Texture::unbind()
{
	glBindTexture(_target, 0);
	_isBound = false;
}

void Texture::parameter(Texture::ParamName name, Texture::Param param)
{
	assert(_isBound && "Texture is not bound");

	glTexParameteri(_target, static_cast<GLenum>(name), static_cast<GLint>(param));
}

/*
void Texture::parameter(GLenum name, GLfloat param)
{
	assert(_isBound && "Texture is not bound");

	glTexParameterf(_target, name, param);
}
*/

Texture::TextureRegion Texture::region(float x, float y, float w, float h)
{
	TextureRegion region;

	// convert pixel coordinates to texture coordinates
	// opengl texture coordinates are [0, 1], left to right, bottom to top

	float width, height;
	
	// widht or height less than 0 signals to use the full texture width or height
	if (w < 0) width = (float)_width;
	if (h < 0) height = (float)_height;

	float x1, x2, y1, y2;

	x1 = x / _width;
	x2 = ( x + w ) / _width;
	y1 = y / _height;
	y2 = (y + h) / _height;

	// calculate the corners of the region using points (x1, y1) & (x2, y2)

	region.bottomLeft.s = x1;
	region.bottomLeft.t = y1;

	region.topLeft.s = x1;
	region.topLeft.t = y2;

	region.topRight.s = x2;
	region.topRight.t = y2;

	region.bottomRight.s = x2;
	region.bottomRight.t = y1;

	return region;
}

void Texture::setTarget(Texture::Target target)
{
	_target = static_cast<GLenum>(target);
}

GLuint Texture::handle()
{
	return _id;
}

bool Texture::isBound()
{
	return _isBound;
}

void Texture::destroy()
{
	glDeleteTextures(1, &_id);
}

Texture::~Texture()
{
	destroy();
}