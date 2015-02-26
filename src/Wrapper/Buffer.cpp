
#include "SGL/Wrapper/Buffer.h"

using namespace sgl;

Buffer::Buffer() : Buffer::Buffer(Target::ARRAY, Usage::STATIC_DRAW)
{
}

Buffer::Buffer(Target target, Usage usage)
{
	create();
	setTarget(target);
	setUsage(usage);
}

void Buffer::create()
{
	glGenBuffers(1, &_id);
}

void Buffer::bind()
{
	glBindBuffer(_target, _id);
}

void Buffer::unbind()
{
	glBindBuffer(_target, 0);
}

void Buffer::setData(void * buffer, int size)
{
	bind();
	glBufferData(_target, size, buffer, _usage);
	unbind();
}

void Buffer::subData(void * buffer, int offset, int size)
{
	glBufferSubData(_target, offset, size, buffer);
}

void Buffer::setTarget(Target target)
{
	_target = static_cast<GLenum>(target);
}

void Buffer::setUsage(Usage usage)
{
	_usage = static_cast<GLenum>(usage);
}

GLuint Buffer::getID() const
{
	return _id;
}

void Buffer::destroy()
{
	glDeleteBuffers(1, &_id);
}

Buffer::~Buffer()
{
	destroy();
}