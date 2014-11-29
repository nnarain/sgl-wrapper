
#include "RenderBuffer.h"

using namespace sgl;

RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &_rbo);
}

void RenderBuffer::bind(GLuint target)
{
	glBindRenderbuffer(target, _rbo);
}

void RenderBuffer::unbind(GLuint target)
{
	glBindRenderbuffer(target, 0);
}

void RenderBuffer::storage(GLuint component, int w, int h)
{
	glRenderbufferStorage(GL_RENDERBUFFER, component, w, h);
}

GLuint RenderBuffer::handle() const
{
	return _rbo;
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &_rbo);
}