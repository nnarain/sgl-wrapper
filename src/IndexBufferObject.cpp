
#include "IndexBufferObject.h"

using namespace sgl;

IndexBufferObject::IndexBufferObject(int *indexBuffer, int len)
{
	_len = len;
	glGenBuffers(1, &_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, len * sizeof(int), indexBuffer, GL_STATIC_DRAW);
}

void IndexBufferObject::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

int IndexBufferObject::length() const
{
	return _len;
}

IndexBufferObject::~IndexBufferObject()
{
	glDeleteBuffers(1, &_id);
}