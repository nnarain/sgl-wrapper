
#include "SGL/ArrayBuffer.h"

#include "SGL/SGLException.h"

using namespace sgl;

ArrayBuffer::ArrayBuffer()
{
	glGenBuffers(1, &_id);
}

void ArrayBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void ArrayBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ArrayBuffer::data(void * buffer, int size)
{
	glBufferData(GL_ARRAY_BUFFER, size, buffer, _usage);
	sglCheckGLError();
}

void ArrayBuffer::subData(void * buffer, int offset, int size)
{
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, buffer);
	sglCheckGLError();
}

void ArrayBuffer::setUsage(GLenum usage)
{
	_usage = usage;
}

ArrayBuffer::~ArrayBuffer()
{
	glDeleteBuffers(1, &_id);
}
