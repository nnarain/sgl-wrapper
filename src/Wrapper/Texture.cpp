
#include "SGL/Wrapper/Texture.h"

#include <memory>
#include <algorithm>

using namespace sgl;

Texture::Texture(Target target, int width, int height, Texture::InternalFormat internalFormat, Texture::Format format) :
	_width(width),
	_height(height),
	_isBound(false)
{
	create();
	setTarget(target);

	_internalFormat = static_cast<GLint>(internalFormat);
	_format         = static_cast<GLenum>(format);
}

void Texture::create()
{
	glGenTextures(1, &_id);
}

void Texture::data(char* pixels)
{
	data(_target, pixels);
}

void Texture::data(Target target, char* pixels)
{
	assert(_isBound && "Texture has not been bound");

	glTexImage2D(static_cast<GLenum>(target), 0, _internalFormat, _width, _height, 0, _format, GL_UNSIGNED_BYTE, pixels);
}

void Texture::bind()
{
	glBindTexture(static_cast<GLenum>(_target), _id);
	_isBound = true;
}

void Texture::bind(Unit unit)
{
	glActiveTexture(static_cast<GLuint>(unit));
	glBindTexture(static_cast<GLenum>(_target), _id);

	_isBound = true;
}

void Texture::unbind()
{
	glBindTexture(static_cast<GLenum>(_target), 0);
	_isBound = false;
}

void Texture::parameter(Texture::ParamName name, Texture::Param param)
{
	assert(_isBound && "Texture is not bound");

	glTexParameteri(static_cast<GLenum>(_target), static_cast<GLenum>(name), static_cast<GLint>(param));
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

	float width = w, height = h;
	
	// widht or height less than 0 signals to use the full texture width or height
	if (w < 0) width = (float)_width;
	if (h < 0) height = (float)_height;

	float x1, x2, y1, y2;

	x1 = x / _width;
	x2 = ( x + width ) / _width;
	y1 = y / _height;
	y2 = (y + height) / _height;

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
	_target = target;
}

Texture::Target Texture::getTarget() const
{
	return _target;
}

GLuint Texture::getId() const
{
	return _id;
}

bool Texture::isBound()
{
	return _isBound;
}

void Texture::setWidth(int w)
{
	_width = w;
}

int Texture::getWidth() const
{
	return _width;
}

void Texture::setHeight(int h)
{
	_height = h;
}

int Texture::getHeight() const
{
	return _height;
}

void Texture::destroy()
{
	glDeleteTextures(1, &_id);
}

Texture::~Texture()
{
	destroy();
}