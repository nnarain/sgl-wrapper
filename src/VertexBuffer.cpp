
#include "SGL/VertexBuffer.h"

using namespace sgl;

VertexBuffer::VertexBuffer()
{ 
	create();
}

VertexBuffer::VertexBuffer(Usage usage)
{
	create();
	setUsage(usage);
}

void VertexBuffer::create()
{
	glGenBuffers(1, &_id);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::data(void * buffer, int size)
{
	glBufferData(GL_ARRAY_BUFFER, size, buffer, _usage);
}

void VertexBuffer::subData(void * buffer, int offset, int size)
{
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, buffer);
}

void VertexBuffer::setUsage(Usage usage)
{
	_usage = static_cast<GLenum>(usage);
}

void VertexBuffer::destroy()
{
	glDeleteBuffers(1, &_id);
}

VertexBuffer::~VertexBuffer()
{
	destroy();
}