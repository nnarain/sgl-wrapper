#include "VertexAttribute.h"

using namespace sgl;

VertexAttribute::VertexAttribute() : VertexAttribute("", 0, 0, 0)
{
}

VertexAttribute::VertexAttribute(std::string name, int numElements, int numComponents, int componentSize)
{
	_attrName = name;
	_numElements = numElements;
	_numComponents = numComponents;
	_sizeComponent = componentSize;
}

void VertexAttribute::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexAttribute::createBuffer(void * data)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, _numElements * _numComponents * _sizeComponent, data, GL_STATIC_DRAW);
}

std::string VertexAttribute::getName() const
{
	return _attrName;
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