#include "SGL/Wrapper/FrameBuffer.h"
#include "SGL/Util/Exception.h"

using namespace sgl;

FrameBuffer::FrameBuffer() :
	_attachments(new std::vector<GLenum>)
{
	glGenFramebuffers(1, &_id);
}

void FrameBuffer::bind(Mode mode)
{
	_target = static_cast<GLuint>(mode);
	glBindFramebuffer(_target, _id);
}


void FrameBuffer::unbind()
{
	glBindFramebuffer(_target, 0);
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
	glDrawBuffers(_attachments->size(), &(*_attachments)[0]);
}

void FrameBuffer::addAttachment(GLenum attachment)
{
	_attachments->push_back(attachment);
}

bool FrameBuffer::error()
{
	return glCheckFramebufferStatus(_target) != GL_FRAMEBUFFER_COMPLETE;
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &_id);
	delete _attachments;
}