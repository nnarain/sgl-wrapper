
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

Texture::~Texture()
{
	glDeleteTextures(1, id());
}