
#include "Model.h"

using namespace sgl;

Model::Model(int faces)
{
	_drawType = GL_TRIANGLES;
	_drawStart = 0;
	_drawCount = faces * 2 * 3;

	_attribs = new std::vector<VertexAttribute_t>();
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
	glBufferData(GL_ARRAY_BUFFER, len, data, GL_STATIC_DRAW);

	//
	int i;
	for (i = 0; i < _attribs->size(); ++i){
		
		VertexAttribute_t attrib = (*_attribs)[i];
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

void Model::addAttribute(ShaderProgram& shader, std::string name, int numComponents)
{
	VertexAttribute_t attrib;
	attrib.loc = shader.getAttributeLocation(name);
	attrib.numComponents = numComponents;

	_attribs->push_back(attrib);
}

int Model::offset(int idx)
{
	int i;
	int off = 0;

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