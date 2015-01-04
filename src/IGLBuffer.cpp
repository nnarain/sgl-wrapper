
#include "SGL/IGLBuffer.h"
#include "SGL/SGLException.h"

#include <cassert>

using namespace sgl;

IGLBuffer::IGLBuffer(GLuint defaultTarget)
{
	_defaultTarget = defaultTarget;
	_currentTarget = 0;
	_isBound = false;
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
	assert(_isBound && "buffer is already unbound");

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