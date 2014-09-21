
#include "StaticModel.h"

using namespace sgl;

StaticModel::StaticModel()
{
}

void StaticModel::bindVBO(float * buffer, int len)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, len * sizeof(float), buffer, GL_STATIC_DRAW);
}

void StaticModel::bindIBO(int *buffer, int idx, int len)
{
	glGenBuffers(1, &ibos[idx]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[idx]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, len * sizeof(int), buffer, GL_STATIC_DRAW);

	numIndices[idx] = len;
}

void StaticModel::setNumMeshes(int num)
{
	numMeshes = num;

	ibos = new GLuint[num];
	numIndices = new int[num];
}

GLuint StaticModel::getVBO() const
{
	return vbo;
}

GLuint StaticModel::getIBO(int idx) const
{
	return ibos[idx];
}

int StaticModel::getNumberOfIndices(int idx) const
{
	return numIndices[idx];
}

int StaticModel::getNumberOfMeshes() const
{
	return numMeshes;
}

StaticModel::~StaticModel()
{
	int i;
	for (i = 0; i < numMeshes; i++){
		glDeleteBuffers(1, &ibos[i]);
	}
	delete[] ibos;
	delete[] numIndices;

	glDeleteBuffers(1, &vbo);
}
