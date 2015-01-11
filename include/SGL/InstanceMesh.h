
#pragma once

#ifndef INSTANCEMESH_H
#define INSTANCEMESH_H

#include "SGLExport.h"

#include "ArrayBuffer.h"
#include "VertexAttribute.h"

#include <vector>

namespace sgl
{
	SGLCLASS InstanceMesh
	{
	public:

		InstanceMesh(GLuint drawType, GLuint drawCount, GLenum usage);
		~InstanceMesh();

		void bind();
		void draw();
		void unbind();

		void create(int meshStride, int instanceStride);

		void addMeshAttribute(const VertexAttribute& a);
		void addInstanceAttribute(const VertexAttribute& a);

		void setMeshData(void * buffer, int size);
		void setInstanceData(void * buffer, int size);

		void setInstances(unsigned int n);

	private:
		//! Vertex Array Object handle
		GLuint _vao;

		//! Buffer to store mesh data
		ArrayBuffer _meshBuffer;

		//! Buffer to store instance data
		ArrayBuffer _instanceBuffer;

		//! mesh attribute buffer
		std::vector<VertexAttribute>* _meshAttributes;

		//! object attribute buffer
		std::vector<VertexAttribute>* _instanceAttributes;

		//!
		GLuint _drawType;
		GLuint _drawCount;

		//! the number of instances to render
		unsigned int _numInstances;

		//! Attribute location
		int _attribLoc;

		/* Member functions */

		void setVertexPointers(const VertexAttribute& attrib, std::vector<VertexAttribute>& attribs, int idx, int stride);

		int offset(std::vector<VertexAttribute>& attrib, int idx);
	};
};


#endif
