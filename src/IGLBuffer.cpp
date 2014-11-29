
#include "IGLBuffer.h"

using namespace sgl;

IGLBuffer::IGLBuffer(GLuint defaultTarget)
{
	_defaultTarget = defaultTarget;
}

GLuint IGLBuffer::handle() const
{
	return _id;
}

IGLBuffer::~IGLBuffer()
{
	
}