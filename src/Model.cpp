
#include "SGL/Model.h"
#include "SGL/SGLException.h"

using namespace sgl;

Model::Model(GLenum drawType, int drawCount, GLenum usage)
{
	_drawType = drawType;
	_drawStart = 0;
	_drawCount = drawCount;
	_usage = usage;

	_attribs = new std::vector<VertexAttribute>();
}

void Model::create(float *data, int len, int stride)
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

void Model::bind()
{
	glBindVertexArray(_vao);
}

void Model::draw()
{
	glDrawArrays(_drawType, _drawStart, _drawCount);
}

void Model::unbind()
{
	glBindVertexArray(0);
}

void Model::addAttribute(ShaderProgram& shader, std::string name)
{
	_attribs->push_back(shader.getAttribute(name));
}

int Model::offset(int idx)
{
	int i;
	int off = 0;

	// calculate the offset in the vertex buffer for the current index
	for (i = 0; i < idx; i++){
		off += (*_attribs)[i].numComponents;
	}

	return off * sizeof(float);
}

Model::~Model(void)
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);

	delete _attribs;
}