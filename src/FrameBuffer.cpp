
#include "FrameBuffer.h"

using namespace sgl;

FrameBuffer::FrameBuffer() : IGLBuffer(GL_FRAMEBUFFER)
{
	glGenFramebuffers(1, &_id);
}

void FrameBuffer::bind(GLuint target)
{
	IGLBuffer::bind(target);
	glBindFramebuffer(target, _id);
}

void FrameBuffer::bind()
{
	bind(_defaultTarget);
}

void FrameBuffer::unbind()
{
	IGLBuffer::unbind();
	glBindFramebuffer(_currentTarget, 0);
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
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE;
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &_id);
}
