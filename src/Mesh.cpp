
#include "SGL/Mesh.h"
#include "SGL/SGLException.h"

#include <cassert>

#include <iostream>

using namespace sgl;

Mesh::Mesh(GLenum drawType, int drawCount, VertexBuffer::Usage usage) :
	_vao(),
	_vbo(usage),
	_drawType(drawType),
	_drawCount(drawCount),
	_drawStart(0),
	_attribs(new std::vector<VertexAttribute>),
	_isBound(false)
{
}

Mesh::Mesh() : Mesh::Mesh(GL_TRIANGLES, 0, VertexBuffer::Usage::STATIC)
{
}

Mesh::Mesh(const Mesh& that) : Mesh::Mesh(that._drawType, that._drawCount, that._usage)
{
	// copy attributes
	for (const VertexAttribute& v : that.getVertexAttributes())
	{
		_attribs->push_back(v);
	}

	// TODO : copy contents of buffer
}

void Mesh::create(void *data, int size, int stride)
{
	// start saving the state
	bind();

	// set the vertex buffer data
	_vbo.bind();
	_vbo.data(data, size);

	// iterate over the model attributes and set offsets in the buffer
	unsigned int i;
	for (i = 0; i < _attribs->size(); ++i){
		
		VertexAttribute attrib = (*_attribs)[i];
		glEnableVertexAttribArray(attrib.loc);
		glVertexAttribPointer(
			attrib.loc,
			attrib.numComponents,
			GL_FLOAT,
			GL_FALSE,
			stride,
			(const GLvoid*)offset(i)
		);

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

	glDrawArrays(_drawType, _drawStart, _drawCount);
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

void Mesh::setDrawType(GLenum drawtype)
{
	_drawType = drawtype;
}

void Mesh::setDrawCount(GLint count)
{
	_drawCount = count;
}

int Mesh::offset(int idx)
{
	int i;
	int off = 0;

	// calculate the offset in the vertex buffer for the current index
	for (i = 0; i < idx; i++){
		off += (*_attribs)[i].numComponents;
	}

	return off * sizeof(float);
}

const std::vector<VertexAttribute> &Mesh::getVertexAttributes() const
{
	return *(_attribs);
}

Mesh& Mesh::operator=(const Mesh& that)
{
	_drawType  = that._drawType;
	_drawCount = that._drawCount;
	_drawStart = that._drawStart;
	_usage     = that._usage;

	// copy attributes
	_attribs = that._attribs;

	// TODO : copy buffer data

	return *this;
}

Mesh::~Mesh(void)
{
	delete _attribs;
}