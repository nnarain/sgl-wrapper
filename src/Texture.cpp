
#include "Texture.h"

using namespace sgl;

Texture::Texture()
{
}

void Texture::create()
{
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
}