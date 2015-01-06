
#include "SGL/ArrayBuffer.h"

using namespace sgl;

ArrayBuffer::ArrayBuffer() : IGLBuffer(GL_ARRAY_BUFFER)
{
	glGenBuffers(1, id());
}

void ArrayBuffer::bind()
{
	IGLBuffer::bind();
	glBindBuffer(defaultTarget(), handle());
}

void ArrayBuffer::unbind()
{
	IGLBuffer::unbind();
	glBindBuffer(defaultTarget(), 0);
}

void ArrayBuffer::data(void * buffer, int size)
{
	glBufferData(defaultTarget(), size, buffer, _usage);
}

void ArrayBuffer::setUsage(GLenum usage)
{
	_usage = usage;
}

ArrayBuffer::~ArrayBuffer()
{
	glDeleteBuffers(1, id());
}
