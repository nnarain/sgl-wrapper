
#include "IGLBuffer.h"

using namespace sgl;

IGLBuffer::IGLBuffer(GLuint defaultTarget)
{
	_defaultTarget = defaultTarget;
	_currentTarget = 0;
}

void IGLBuffer::bind(GLuint target)
{
	_currentTarget = target;
	_isBound = true;
}

void IGLBuffer::bind()
{
	_isBound = true;
}

void IGLBuffer::unbind()
{
	_isBound = false;
}

void IGLBuffer::setDefaultTarget(GLuint target)
{
	_defaultTarget = target;
}

GLuint IGLBuffer::handle() const
{
	return _id;
}

bool IGLBuffer::isBound() const
{
	return _isBound;
}

GLuint* IGLBuffer::id()
{
	return &_id;
}

GLuint IGLBuffer::defaultTarget() const
{
	return _defaultTarget;
}

GLuint IGLBuffer::currentTarget() const
{
	return _currentTarget;
}

IGLBuffer::~IGLBuffer()
{
	
}