
#include "FrameBuffer.h"

using namespace sgl;

FrameBuffer::FrameBuffer() : IGLBuffer(GL_FRAMEBUFFER)
{
	glGenFramebuffers(1, id());
}

void FrameBuffer::bind(GLuint target)
{
	IGLBuffer::bind(target);
	glBindFramebuffer(target, *id());
}

void FrameBuffer::bind()
{
	bind(defaultTarget());
}

void FrameBuffer::unbind()
{
	IGLBuffer::unbind();
	glBindFramebuffer(currentTarget(), 0);
}

void FrameBuffer::setTexture(Texture& texture, GLuint attachment)
{
	glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture.handle(), 0);
}

void FrameBuffer::setRenderBuffer(RenderBuffer& renderBuffer, GLuint attachment)
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderBuffer.handle());
}

void FrameBuffer::setDrawBuffer()
{
	glDrawBuffers(_attachments.size(), &_attachments[0]);
}

void FrameBuffer::addAttachment(GLenum attachment)
{
	_attachments.push_back(attachment);
}

bool FrameBuffer::error()
{
	return glCheckFramebufferStatus(currentTarget()) != GL_FRAMEBUFFER_COMPLETE;
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, id());
}
