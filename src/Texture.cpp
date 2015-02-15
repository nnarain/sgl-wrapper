
#include "SGL/Texture.h"
#include "SGL/SGLException.h"

#include <memory>
#include <algorithm>

using namespace sgl;

Texture::Texture(int width, int height, GLint internalFormat, GLenum format) :
	_width(width),
	_height(height),
	_internalFormat(internalFormat),
	_format(format),
	_isBound(false)
{
	glGenTextures(1, &_id);
}

Texture::Texture(const Texture& that) : Texture(that._width, that._height, that._internalFormat, that._format)
{
	char *pixels = new char[_width * _height];

	// get the texture data
	glBindTexture(GL_TEXTURE_2D, _id);
	glGetTexImage(GL_TEXTURE_2D, 0, _format, GL_UNSIGNED_BYTE, pixels);

	// set into new texture
	data(pixels);
}


void Texture::data(char* pixels)
{
	data(GL_TEXTURE_2D, pixels);
}

void Texture::data(GLuint target, char* pixels)
{
	assert(_isBound && "Texture has not been bound");

	glTexImage2D(target, 0, _internalFormat, _width, _height, 0, _format, GL_UNSIGNED_BYTE, pixels);
	sglCheckGLError();
}

void Texture::bind(GLuint target)
{
	glActiveTexture(target);
	glBindTexture(GL_TEXTURE_2D, _id);

	_isBound = true;
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	_isBound = false;
}

void Texture::parameter(GLenum name, GLint param)
{
	assert(_isBound && "Texture is not bound");

	glTexParameteri(GL_TEXTURE_2D, name, param);
	sglCheckGLError();
}

void Texture::parameter(GLenum name, GLfloat param)
{
	assert(_isBound && "Texture is not bound");

	glTexParameterf(GL_TEXTURE_2D, name, param);
	sglCheckGLError();
}

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

GLuint Texture::handle()
{
	return _id;
}

bool Texture::isBound()
{
	return _isBound;
}

void sgl::swap(Texture& first, Texture& second)
{
	using std::swap;

	swap(first._format, second._format);
	swap(first._height, second._height);
	swap(first._id, second._id);
	swap(first._internalFormat, second._internalFormat);
	swap(first._isBound, second._isBound);
	swap(first._width, second._width);
}

Texture& Texture::operator=(Texture that)
{
	swap(*this, that);
	return *this;
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}