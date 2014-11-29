
#include "Texture.h"

using namespace sgl;

Texture::Texture() : IGLBuffer(GL_TEXTURE_2D)
{
}

void Texture::create(GLint internalFormat, GLenum format, int w, int h, char* pixels)
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, format, GL_UNSIGNED_BYTE, pixels);
}

void Texture::bind(GLuint target)
{
	IGLBuffer::bind(_defaultTarget);
	glActiveTexture(target);
	glBindTexture(_defaultTarget, _id);
}

void Texture::bind()
{
	return;
}

void Texture::unbind()
{
	IGLBuffer::unbind();
	glBindTexture(_currentTarget, 0);
}

void Texture::parameter(GLenum name, GLint param)
{
	glTexParameteri(GL_TEXTURE_2D, name, param);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}