
#include "SGL/Texture.h"
#include "SGL/SGLException.h"

using namespace sgl;

Texture::Texture(int width, int height, GLint internalFormat, GLenum format) : IGLBuffer(GL_TEXTURE_2D)
{
	_width = width;
	_height = height;
	_internalFormat = internalFormat;
	_format = format;

	glGenTextures(1, id());
}

Texture::Texture(GLuint target, int width, int height, GLint internalFormat, GLenum format) : IGLBuffer(target)
{
	_width = width;
	_height = height;
	_internalFormat = internalFormat;
	_format = format;

	glGenTextures(1, id());
}

void Texture::data(char* pixels)
{
	data(currentTarget(), pixels);
}

void Texture::data(GLuint target, char* pixels)
{
	glTexImage2D(target, 0, _internalFormat, _width, _height, 0, _format, GL_UNSIGNED_BYTE, pixels);
	sglCheckGLError();
}

void Texture::bind(GLuint target)
{
	IGLBuffer::bind(defaultTarget());
	glActiveTexture(target);
	glBindTexture(defaultTarget(), handle());
}

void Texture::bind()
{
	glBindTexture(defaultTarget(), handle());
}

void Texture::unbind()
{
	if (isBound())
	{
		IGLBuffer::unbind();
		glBindTexture(currentTarget(), 0);
	}
}

void Texture::parameter(GLenum name, GLint param)
{
	if (isBound()){
		glTexParameteri(currentTarget(), name, param);
		sglCheckGLError();
	}
}

void Texture::parameter(GLenum name, GLfloat param)
{
	if (isBound()){
		glTexParameterf(currentTarget(), name, param);
		sglCheckGLError();
	}
}

Texture::TextureRegion Texture::region(float x, float y, float w, float h)
{
	TextureRegion region;

	// convert pixel coordinates to texture coordinates
	// opengl texture coordinates are [0, 1], left to right, bottom to top

	float x1, x2, y1, y2;

	// pixel x to texture s
	float texS = x / _width;
	// pixel y to texture y
	float texT = y / _height;
	// pixel width to texture width
	float texW = w / _width;
	// pixel height to texture height
	float texH = h / _height;

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

Texture::~Texture()
{
	glDeleteTextures(1, id());
}