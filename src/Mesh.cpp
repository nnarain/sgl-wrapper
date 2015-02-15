
#include "SGL/Mesh.h"
#include "SGL/SGLException.h"

#include <cassert>

#include <iostream>

using namespace sgl;

Mesh::Mesh(GLenum drawType, int drawCount, GLenum usage) :
	_drawType(drawType),
	_drawCount(drawCount),
	_usage(usage),
	_drawStart(0),
	_attribs(new std::vector<VertexAttribute>),
	_isBound(false)
{
	// generate buffer
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
}

Mesh::Mesh() : Mesh::Mesh(GL_TRIANGLES, 0, GL_STATIC_DRAW)
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
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, _usage);

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

	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Mesh::bind()
{
	glBindVertexArray(_vao);
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

	glBindVertexArray(0);
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

GLuint Mesh::handle() const
{
	return _vbo;
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
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);

	delete _attribs;
}