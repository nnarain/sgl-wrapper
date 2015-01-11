
#include "SGL/ArrayBuffer.h"

#include "SGL/SGLException.h"

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
	sglCheckGLError();
}

void ArrayBuffer::subData(void * buffer, int offset, int size)
{
	glBufferSubData(defaultTarget(), offset, size, buffer);
	sglCheckGLError();
}

void ArrayBuffer::setUsage(GLenum usage)
{
	_usage = usage;
}

ArrayBuffer::~ArrayBuffer()
{
	glDeleteBuffers(1, id());
}
