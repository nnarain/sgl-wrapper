
#include "SGL/InstanceMesh.h"
#include "SGL/VertexAttribute.h"

#include "SGL/SGLException.h"

using namespace sgl;

InstanceMesh::InstanceMesh(GLuint drawType, GLuint drawCount, GLenum usage)
{
	_drawType = drawType;
	_drawCount = drawCount;

	_meshBuffer.setUsage(GL_STATIC_DRAW);
	_instanceBuffer.setUsage(usage);

	_meshAttributes = new std::vector<VertexAttribute>();
	_instanceAttributes = new std::vector<VertexAttribute>();

	glGenVertexArrays(1, &_vao);
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

	_meshBuffer.bind();

	// enable and set offsets for the mesh vertex attributes
	for (i = 0; i < _meshAttributes->size(); ++i)
	{
		const VertexAttribute& attrib = (*_meshAttributes)[i];
		setVertexPointers(attrib, (*_meshAttributes), i, meshStride);	
	}
	
	_meshBuffer.unbind();

	// enable and set the offsets for the instance vertex attributes

	_instanceBuffer.bind();

	for (i = 0; i < _instanceAttributes->size(); ++i)
	{
		const VertexAttribute &attrib = (*_instanceAttributes)[i];
		setVertexPointers(attrib, *_instanceAttributes, i, instanceStride);
	}

	_instanceBuffer.unbind();

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

		// if has 4 components
		if (attrib.numComponents % 4 == 0)
		{
			int off = offset(*_instanceAttributes, idx);

			for (i = 0; i < 4; ++i)
			{
				GLuint loc = attrib.loc + i;

				glEnableVertexAttribArray(loc);

				glVertexAttribPointer(
					loc,
					4,
					GL_FLOAT,
					GL_FALSE,
					stride,
					//(const GLvoid*)(sizeof(float) * i * 4)
					(const GLvoid *)(off + (sizeof(float) * i * 4))
				);

				glVertexAttribDivisor(attrib.loc + i, 1);
			}
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
	_meshBuffer.bind();
	_meshBuffer.data(buffer, size);
	_meshBuffer.unbind();
}

void InstanceMesh::setInstanceData(void * buffer, int size)
{
	_instanceBuffer.bind();
	_instanceBuffer.data(buffer, size);
	_instanceBuffer.unbind();
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
}
