#include "SGL/GL/FrameBuffer.h"
#include "SGL/Util/Exception.h"

#include <cassert>

using namespace sgl;

FrameBuffer::FrameBuffer() :
	_attachments(new std::vector<GLenum>),
	_isBound(false)
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

	_isBound = true;
}


void FrameBuffer::unbind()
{
	assert(_isBound);

	glBindFramebuffer(static_cast<GLuint>(_target), 0);

	_isBound = false;
}

void FrameBuffer::setTexture(Texture& texture, FrameBuffer::Attachment attachment)
{
	assert(_isBound);

	glFramebufferTexture(
		static_cast<GLuint>(_target), 
		static_cast<GLuint>(attachment), 
		texture.getId(), 
		0
	);
}

void FrameBuffer::setTexture2D(const Texture &texture, Attachment attachment)
{
	assert(_isBound);

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
	assert(_isBound);

	glFramebufferRenderbuffer(
		static_cast<GLuint>(_target),
		static_cast<GLuint>(attachment), 
		GL_RENDERBUFFER, 
		renderBuffer.handle()
	);
}

void FrameBuffer::setDrawBuffer(Attachment a)
{
	assert(_isBound);

	glDrawBuffer(static_cast<GLenum>(a));
}

void FrameBuffer::setDrawBuffers(void)
{
	assert(_isBound);

	glDrawBuffers(_attachments->size(), &(*_attachments)[0]);
}

void FrameBuffer::setReadBuffer(Attachment a)
{
	assert(_isBound);

	glReadBuffer(static_cast<GLenum>(a));
}

void FrameBuffer::addAttachment(Attachment attachment)
{
	assert(_isBound);

	_attachments->push_back(static_cast<GLenum>(attachment));
}

void FrameBuffer::checkError()
{
	assert(_isBound);

	GLenum ret = glCheckFramebufferStatus(static_cast<GLenum>(_target));

	if (ret != GL_FRAMEBUFFER_COMPLETE)
	{
		std::string what;

		switch (ret)
		{
		case GL_FRAMEBUFFER_UNDEFINED:
			what = "Framebuffer undefined";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			what = "incomplete attachment";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			what = "incomplete missing attachment";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			what = "incomplete draw buffer";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			what = "incomplete read buffer";
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			what = "unsupported";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			what = "incomplete multisample";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			what = "incomplete layer targets";
			break;

		case GL_INVALID_ENUM:
			what = "Invalid Enum";
			break;

		default:
			what = "Unknown";
			break;
		}

		throw Exception("Framebuffer Error: " + what);
	}
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