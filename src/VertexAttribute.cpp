#include "VertexAttribute.h"

using namespace sgl;

VertexAttribute::VertexAttribute(GLuint loc, int numComponents)
{
	_loc = loc;
	_numComponents = numComponents;
}

GLuint VertexAttribute::getLocation() const
{
	return _loc;
}

int VertexAttribute::getNumComponents() const
{
	return _numComponents;
}

VertexAttribute::~VertexAttribute()
{
	glDeleteBuffers(1, &id);
}