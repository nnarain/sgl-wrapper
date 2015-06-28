
#include "SGL/GL/Buffer.h"

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
	glBindBuffer(static_cast<GLenum>(_target), _id);
}

void Buffer::unbind()
{
	glBindBuffer(static_cast<GLenum>(_target), 0);
}

void Buffer::setData(void * buffer, int size)
{
	glBufferData(static_cast<GLenum>(_target), size, buffer, static_cast<GLenum>(_usage));
}

void Buffer::subData(void * buffer, int offset, int size)
{
	glBufferSubData(static_cast<GLenum>(_target), offset, size, buffer);
}

void Buffer::setTarget(Target target)
{
	_target = target;
}

void Buffer::setUsage(Usage usage)
{
	_usage = usage;
}

GLuint Buffer::getId() const
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