
#include "SGL/InstanceMesh.h"
#include "SGL/VertexAttribute.h"

#include "SGL/SGLException.h"

using namespace sgl;

#define MESH_BUFFER     0
#define INSTANCE_BUFFER 1

InstanceMesh::InstanceMesh(GLuint drawType, GLuint drawCount, GLenum usage)
{
	_drawType = drawType;
	_drawCount = drawCount;
	_usage = usage;

	_meshAttributes = new std::vector<VertexAttribute>();
	_instanceAttributes = new std::vector<VertexAttribute>();

	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);
}

void InstanceMesh::bind()
{
	glBindVertexArray(_vao);
}

void InstanceMesh::draw()
{
	glDrawArraysInstanced(_drawType, 0, _drawCount, _numInstances);
}

void InstanceMesh::unbind()
{
	glBindVertexArray(0);
}

void InstanceMesh::create(int meshStride, int instanceStride)
{
	unsigned int i;

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[MESH_BUFFER]);

	// enable and set offsets for the mesh vertex attributes
	for (i = 0; i < _meshAttributes->size(); ++i)
	{
		const VertexAttribute& attrib = (*_meshAttributes)[i];
		setVertexPointers(attrib, (*_meshAttributes), i, meshStride);	
	}

	// enable and set the offsets for the instance vertex attributes

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[INSTANCE_BUFFER]);

	for (i = 0; i < _instanceAttributes->size(); ++i)
	{
		const VertexAttribute &attrib = (*_instanceAttributes)[i];
		setVertexPointers(attrib, *_instanceAttributes, i, instanceStride);
	}

	//_instanceBuffer.unbind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void InstanceMesh::setVertexPointers(const VertexAttribute& attrib, std::vector<VertexAttribute>& attribs, int idx, int stride)
{
	if (attrib.numComponents <= 4)
	{
		glEnableVertexAttribArray(attrib.loc);
		glVertexAttribPointer(
			attrib.loc,
			attrib.numComponents,
			GL_FLOAT,
			GL_FALSE,
			stride,
			(const GLvoid*)offset(attribs, idx)
		);

		glVertexAttribDivisor(attrib.loc, 0);
	}
	else
	{
		int i;

		int numComponents;

		if (attrib.numComponents % 4 == 0)
		{
			numComponents = 4;
		}
		else
		{
			numComponents = 3;
		}

		int off = offset(*_instanceAttributes, idx);

		for (i = 0; i < numComponents; ++i)
		{
			GLuint loc = attrib.loc + i;

			glEnableVertexAttribArray(loc);

			glVertexAttribPointer(
				loc,
				numComponents,
				GL_FLOAT,
				GL_FALSE,
				stride,
				//(const GLvoid*)(sizeof(float) * i * 4)
				(const GLvoid *)(off + (sizeof(float) * i * numComponents))
			);

			glVertexAttribDivisor(attrib.loc + i, 1);
		}
	}

	sglCheckGLError();
}

void InstanceMesh::addMeshAttribute(const VertexAttribute &a)
{
	_meshAttributes->push_back(a);
}

void InstanceMesh::addInstanceAttribute(const VertexAttribute& a)
{
	_instanceAttributes->push_back(a);
}

void InstanceMesh::setInstances(unsigned int n)
{
	_numInstances = n;
}

void InstanceMesh::setMeshData(void * buffer, int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[MESH_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstanceMesh::setInstanceData(void * buffer, int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[INSTANCE_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, size, buffer, _usage);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int InstanceMesh::offset(std::vector<VertexAttribute>& attrib, int idx)
{
	int i;
	int off = 0;

	// calculate the offset in the vertex buffer for the current index
	for (i = 0; i < idx; i++){
		off += attrib[i].numComponents;
	}

	return off * sizeof(float);
}

InstanceMesh::~InstanceMesh()
{
	delete _meshAttributes;
	delete _instanceAttributes;

	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(2, _vbo);
}
