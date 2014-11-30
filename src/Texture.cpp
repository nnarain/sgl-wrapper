
#include "Texture.h"

using namespace sgl;

Texture::Texture() : IGLBuffer(GL_TEXTURE_2D)
{
}

void Texture::create(GLint internalFormat, GLenum format, int w, int h, char* pixels)
{
	glGenTextures(1, id());
	glBindTexture(GL_TEXTURE_2D, *id());
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, format, GL_UNSIGNED_BYTE, pixels);
}

void Texture::bind(GLuint target)
{
	IGLBuffer::bind(defaultTarget());
	glActiveTexture(target);
	glBindTexture(defaultTarget(), *id());
}

void Texture::bind()
{
	return;
}

void Texture::unbind()
{
	IGLBuffer::unbind();
	glBindTexture(currentTarget(), 0);
}

void Texture::parameter(GLenum name, GLint param)
{
	glTexParameteri(GL_TEXTURE_2D, name, param);
}

Texture::~Texture()
{
	glDeleteTextures(1, id());
}