#include "VertexAttribute.h"

using namespace sgl;

VertexAttribute::VertexAttribute(GLuint loc, int numComponents)
{
	_loc = loc;
	_numComponents = numComponents;
}

void VertexAttribute::bind()
{
//	glBindBuffer(GL_ARRAY_BUFFER, id);
}

/*
void VertexAttribute::createBuffer(void * data, int numElements, int numComponents, int componentSize)
{
	_numElements = numElements;
	_numComponents = numComponents;
	_sizeComponent = componentSize;

	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, _numElements * _numComponents * _sizeComponent, data, GL_STATIC_DRAW);
}
*/

GLuint VertexAttribute::getLocation() const
{
	return _loc;
}

int VertexAttribute::getNumComponents() const
{
	return _numComponents;
}

int VertexAttribute::getNumElements() const
{
	return _numElements;
}

int VertexAttribute::getSizeComponents() const
{
	return _sizeComponent;
}

VertexAttribute::~VertexAttribute()
{
	glDeleteBuffers(1, &id);
}