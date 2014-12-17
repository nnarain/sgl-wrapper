
#include "SGL/Mesh.h"
#include "SGL/SGLException.h"

using namespace sgl;

Mesh::Mesh(GLenum drawType, int drawCount, GLenum usage)
{
	_drawType = drawType;
	_drawStart = 0;
	_drawCount = drawCount;
	_usage = usage;

	_attribs = new std::vector<VertexAttribute>();
}

Mesh::Mesh()
{
	_drawType = GL_TRIANGLES;
	_drawStart = 0;
	_drawCount = 0;
	_usage = GL_STATIC_DRAW;

	_attribs = new std::vector<VertexAttribute>();
}

void Mesh::create(float *data, int len, int stride)
{
	// generate buffer
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	// start saving the state
	bind();

	// set the vertex buffer data
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, len, data, _usage);

	// iterate over the model attributes and set offsets in the buffer
	int i;
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

	sglCheckGLError();
}

void Mesh::bind()
{
	glBindVertexArray(_vao);
}

void Mesh::draw()
{
	glDrawArrays(_drawType, _drawStart, _drawCount);
}

void Mesh::unbind()
{
	glBindVertexArray(0);
}

void Mesh::addAttribute(VertexAttribute attrib)
{
	_attribs->push_back(attrib);
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

Mesh::~Mesh(void)
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);

	delete _attribs;
}