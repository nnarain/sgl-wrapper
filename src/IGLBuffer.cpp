
#include "IGLBuffer.h"

using namespace sgl;

IGLBuffer::IGLBuffer(GLuint defaultTarget)
{
	_defaultTarget = defaultTarget;
}

void IGLBuffer::bind(GLuint target)
{
	_currentTarget = target;
}

void IGLBuffer::bind()
{
	_isBound = true;
}

void IGLBuffer::unbind()
{
	_isBound = false;
}

GLuint IGLBuffer::handle() const
{
	return _id;
}

bool IGLBuffer::isBound() const
{
	return _isBound;
}

IGLBuffer::~IGLBuffer()
{
	
}