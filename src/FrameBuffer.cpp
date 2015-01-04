
#include "SGL/FrameBuffer.h"
#include "SGL/SGLException.h"

using namespace sgl;

FrameBuffer::FrameBuffer() : IGLBuffer(GL_FRAMEBUFFER)
{
	glGenFramebuffers(1, id());
	_attachments = new std::vector<GLenum>();
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
	assert(isBound() && "Frame buffer is not bound");

	glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture.handle(), 0);
	sglCheckGLError();
}

void FrameBuffer::setRenderBuffer(RenderBuffer& renderBuffer, GLuint attachment)
{
	assert(isBound() && "Frame buffer is not bound");

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderBuffer.handle());
	sglCheckGLError();
}

void FrameBuffer::setDrawBuffer()
{
	assert(isBound() && "Frame buffer is not bound");

	glDrawBuffers((*_attachments).size(), &(*_attachments)[0]);
}

void FrameBuffer::addAttachment(GLenum attachment)
{
	assert(isBound() && "Frame buffer is not bound");

	(*_attachments).push_back(attachment);
}

bool FrameBuffer::error()
{
	return glCheckFramebufferStatus(currentTarget()) != GL_FRAMEBUFFER_COMPLETE;
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, id());
	delete _attachments;
}
