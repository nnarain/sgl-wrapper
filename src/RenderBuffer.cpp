
#include "RenderBuffer.h"

using namespace sgl;

RenderBuffer::RenderBuffer() : IGLBuffer(GL_RENDERBUFFER)
{
	glGenRenderbuffers(1, id());
}

void RenderBuffer::bind(GLuint target)
{
	IGLBuffer::bind(target);
	glBindRenderbuffer(target, *id());
}

void RenderBuffer::bind()
{
	bind(defaultTarget());
}

void RenderBuffer::unbind()
{
	IGLBuffer::unbind();
	glBindRenderbuffer(currentTarget(), 0);
}

void RenderBuffer::storage(GLuint component, int w, int h)
{
	glRenderbufferStorage(GL_RENDERBUFFER, component, w, h);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, id());
}