
#include "SGL/GL/VertexArray.h"

using namespace sgl;

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_id);
}

void VertexArray::bind()
{
	glBindVertexArray(_id);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_id);
}


