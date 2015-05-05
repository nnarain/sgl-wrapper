#include "SGL/GL/FrameBuffer.h"
#include "SGL/Util/Exception.h"

using namespace sgl;

FrameBuffer::FrameBuffer() :
	_attachments(new std::vector<GLenum>)
{
	glGenFramebuffers(1, &_id);
}

void FrameBuffer::bind()
{
	bind(Target::DEFAULT);
}

void FrameBuffer::bind(Target target)
{
	_target = target;
	glBindFramebuffer(static_cast<GLuint>(_target), _id);
}


void FrameBuffer::unbind()
{
	glBindFramebuffer(static_cast<GLuint>(_target), 0);
}

void FrameBuffer::setTexture(Texture& texture, FrameBuffer::Attachment attachment)
{
	glFramebufferTexture(
		static_cast<GLuint>(_target), 
		static_cast<GLuint>(attachment), 
		texture.getId(), 
		0
	);
}

void FrameBuffer::setTexture2D(const Texture &texture, Attachment attachment)
{
	glFramebufferTexture2D(
		static_cast<GLuint>(_target),
		static_cast<GLenum>(attachment),
		static_cast<GLenum>(texture.getTarget()),
		texture.getId(),
		0
	);
}

void FrameBuffer::setRenderBuffer(RenderBuffer& renderBuffer, Attachment attachment)
{
	glFramebufferRenderbuffer(
		static_cast<GLuint>(_target),
		static_cast<GLuint>(attachment), 
		GL_RENDERBUFFER, 
		renderBuffer.handle()
	);
}

void FrameBuffer::setDrawBuffer(Attachment a)
{
	glDrawBuffer(static_cast<GLenum>(a));
}

void FrameBuffer::setDrawBuffers(void)
{
	glDrawBuffers(_attachments->size(), &(*_attachments)[0]);
}

void FrameBuffer::addAttachment(Attachment attachment)
{
	_attachments->push_back(static_cast<GLenum>(attachment));
}

bool FrameBuffer::error()
{
	return glCheckFramebufferStatus(static_cast<GLenum>(_target)) != GL_FRAMEBUFFER_COMPLETE;
}

GLuint FrameBuffer::getId() const
{
	return _id;
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &_id);
	delete _attachments;
}