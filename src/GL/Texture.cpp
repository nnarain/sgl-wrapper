
#include "SGL/GL/Texture.h"

#include <cassert>
#include <memory>
#include <algorithm>

using namespace sgl;

Texture::Texture(Target target) :
	_target(target),
	_width(0),
	_height(0),
	_isBound(false),
	_currentUnit(Texture::Unit::NONE)
{
	create();
}

Texture::Texture(Target target, int width, int height, Texture::InternalFormat internalFormat, Texture::Format format) :
	_width(width),
	_height(height),
	_isBound(false),
	_currentUnit(Texture::Unit::NONE)
{
	create();
	setTarget(target);

	_internalFormat = internalFormat;
	_format         = format;
}

void Texture::create()
{
	glGenTextures(1, &_id);
}

void Texture::setData(char* pixels)
{
	setData(_target, pixels);
}

void Texture::setData(Target target, char* pixels)
{
	assert(_isBound && "Texture has not been bound");

	glTexImage2D(
		static_cast<GLenum>(target),
		0,
		static_cast<GLint>(_internalFormat),
		_width,
		_height,
		0,
		static_cast<GLenum>(_format),
		GL_UNSIGNED_BYTE,
		pixels
	);
}

void Texture::setCompressedData(char * pixels, unsigned int levels, unsigned int blockSize)
{
	assert(_isBound && "Texture has not been bound");

	unsigned int level;
	unsigned int offset = 0;
	unsigned int width  = _width;
	unsigned int height = _height;

	for (level = 0; level < levels && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;

		glCompressedTexImage2D(
			static_cast<GLuint>(_target),
			level, 
			static_cast<GLenum>(_format),
			width,
			height,
			0,
			size,
			pixels + offset
		);

		offset += size;
		width /= 2;
		height /= 2;
	}
}

void Texture::bind()
{
	glBindTexture(static_cast<GLenum>(_target), _id);
	_isBound = true;
}

void Texture::bind(Unit unit)
{
	assert(unit != Texture::Unit::NONE && "Texture unit cannot be NONE");

	_currentUnit = unit;

	glActiveTexture(static_cast<GLuint>(unit));
	glBindTexture(static_cast<GLenum>(_target), _id);

	_isBound = true;
}

void Texture::unbind()
{
	if (_currentUnit != Texture::Unit::NONE)
	{
		glActiveTexture(static_cast<GLuint>(_currentUnit));
	}

	glBindTexture(static_cast<GLenum>(_target), 0);

	_currentUnit = Texture::Unit::NONE;
	_isBound = false;
}

void Texture::parameter(Texture::ParamName name, Texture::Param param)
{
	assert(_isBound && "Texture is not bound");

	glTexParameteri(static_cast<GLenum>(_target), static_cast<GLenum>(name), static_cast<GLint>(param));
}

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

	region.bottomLeft.x = x1;
	region.bottomLeft.y = y1;

	region.topLeft.x = x1;
	region.topLeft.y = y2;

	region.topRight.x = x2;
	region.topRight.y = y2;

	region.bottomRight.x = x2;
	region.bottomRight.y = y1;

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

void Texture::setInternalFormat(Texture::InternalFormat format)
{
	_internalFormat = format;
}

Texture::InternalFormat Texture::getInternalFormat() const
{
	return _internalFormat;
}

void Texture::setFormat(Texture::Format format)
{
	_format = format;
}

Texture::Format Texture::getFormat() const
{
	return _format;
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

int Texture::getIndex() const
{
	if (_currentUnit == Texture::Unit::NONE)
	{
		return -1;
	}

	return (int)(static_cast<GLuint>(_currentUnit)-static_cast<GLuint>(Texture::Unit::T0));
}

void Texture::destroy()
{
	glDeleteTextures(1, &_id);
}

Texture::~Texture()
{
	destroy();
}