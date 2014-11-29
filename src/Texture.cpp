
#include "Texture.h"

using namespace sgl;

Texture::Texture()
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
	glActiveTexture(target);
	glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::parameter(GLenum name, GLint param)
{
	glTexParameteri(GL_TEXTURE_2D, name, param);
}

GLuint Texture::handle() const
{
	return _id;
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}