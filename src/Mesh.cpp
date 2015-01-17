
#include "SGL/Mesh.h"
#include "SGL/SGLException.h"

#include <cassert>

using namespace sgl;

Mesh::Mesh(GLenum drawType, int drawCount, GLenum usage)
{
	_drawType = drawType;
	_drawStart = 0;
	_drawCount = drawCount;
	_usage = usage;

	_attribs = new std::vector<VertexAttribute>();

	_isBound = false;

	// generate buffer
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
}

Mesh::Mesh()
{
	_drawType = GL_TRIANGLES;
	_drawStart = 0;
	_drawCount = 0;
	_usage = GL_STATIC_DRAW;

	_isBound = false;

	_attribs = new std::vector<VertexAttribute>();

	// generate opengl buffers
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
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

	sglCheckGLError();
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

Mesh::~Mesh(void)
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);

	delete _attribs;
}