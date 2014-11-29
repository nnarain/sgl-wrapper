
#include "RenderBuffer.h"

using namespace sgl;

RenderBuffer::RenderBuffer() : IGLBuffer(GL_RENDERBUFFER)
{
	glGenRenderbuffers(1, &_id);
}

void RenderBuffer::bind(GLuint target)
{
	IGLBuffer::bind(target);
	glBindRenderbuffer(target, _id);
}

void RenderBuffer::bind()
{
	bind(_defaultTarget);
}

void RenderBuffer::unbind()
{
	IGLBuffer::unbind();
	glBindRenderbuffer(_currentTarget, 0);
}

void RenderBuffer::storage(GLuint component, int w, int h)
{
	glRenderbufferStorage(GL_RENDERBUFFER, component, w, h);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &_id);
}