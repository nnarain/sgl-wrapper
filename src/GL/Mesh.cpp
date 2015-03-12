
#include "SGL/GL/Mesh.h"
#include "SGL/Util/Exception.h"

#include <cassert>

#include <iostream>

using namespace sgl;

Mesh::Mesh(Type drawtype, int drawCount, Buffer::Usage usage) :
	_vao(),
	_vbo(Buffer::Target::ARRAY, usage),
	_drawCount(drawCount),
	_drawStart(0),
	_attribs(new std::vector<VertexAttribute>),
	_isBound(false)
{
	setDrawType(drawtype);
}

Mesh::Mesh() : Mesh::Mesh(Type::TRIANGLES, 0, Buffer::Usage::STATIC_DRAW)
{
}

void Mesh::create(int stride)
{
	unsigned int offset = 0;

	// start saving the state
	bind();

	// set the vertex buffer data
	_vbo.bind();

	// iterate over the mesh attributes and set offsets in the buffer
	unsigned int i;
	for (i = 0; i < _attribs->size(); ++i)
	{
		
		VertexAttribute attrib = (*_attribs)[i];
		glEnableVertexAttribArray(attrib.loc);
		glVertexAttribPointer(
			attrib.loc,
			attrib.numComponents,
			GL_FLOAT,
			GL_FALSE,
			stride,
			//(const GLvoid*)offset(i)
			(const GLvoid *)offset
		);

		offset += (*_attribs)[i].numComponents * sizeof(float);
	}

	//
	unbind();
	_vbo.unbind();
}

void Mesh::bind()
{
	_vao.bind();
	_isBound = true;
}

void Mesh::draw()
{
	assert(_isBound && "Mesh has not been bound");

	glDrawArrays(static_cast<GLenum>(_drawType), _drawStart, _drawCount);
}

void Mesh::unbind()
{
	assert(_isBound && "Mesh is not bound");

	_vao.unbind();
	_isBound = false;
}

void Mesh::addAttribute(VertexAttribute attrib)
{
	_attribs->push_back(attrib);
}

void Mesh::setDrawType(Type type)
{
	_drawType = type;
}

void Mesh::setDrawCount(GLint count)
{
	_drawCount = count;
}

Buffer& Mesh::getVBO()
{
	return _vbo;
}

const std::vector<VertexAttribute> &Mesh::getVertexAttributes() const
{
	return *(_attribs);
}


Mesh::~Mesh(void)
{
	delete _attribs;
}