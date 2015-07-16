
#include "SGL/GL/RenderBuffer.h"

using namespace sgl;

RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &_id);
}

void RenderBuffer::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, _id);
}

void RenderBuffer::unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBuffer::storage(Storage component, int w, int h)
{
	glRenderbufferStorage(GL_RENDERBUFFER, static_cast<GLuint>(component), w, h);
}

GLuint RenderBuffer::handle() const
{
	return _id;
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &_id);
}
