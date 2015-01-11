
#pragma once

#ifndef INSTANCEMESH_H
#define INSTANCEMESH_H

#include "SGLExport.h"

#include "ArrayBuffer.h"
#include "VertexAttribute.h"

#include <vector>

namespace sgl
{
	/**
		Use this mesh to apply instance rendering to a mesh
	*/
	SGLCLASS InstanceMesh
	{
	public:

		/**
			
		*/
		InstanceMesh(GLuint drawType, GLuint drawCount, GLenum usage);
		~InstanceMesh();

		void bind();
		void draw();
		void unbind();

		/**
			Setup the vertex pointers in the mesh and instance buffers

			@param meshStride
				stride between mesh data

			@param instanceStride
				stride between instance data
		*/
		void create(int meshStride, int instanceStride);

		/* Adding attributes */

		void addMeshAttribute(const VertexAttribute& a);
		void addInstanceAttribute(const VertexAttribute& a);

		/* Set buffer data */

		/**
			Set mesh data

			@param buffer
				pointer to the vertex buffer

			@param size
				size of the buffer in bytes
		*/
		void setMeshData(void * buffer, int size);

		/**
			Set the instance data

			@param buffer
				pointer to the instance data

			@param size
				size of the buffer in bytes
		*/
		void setInstanceData(void * buffer, int size);

		/* Getter & Setter */

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

		//! Set the primitive type
		GLuint _drawType;
		//! vertex count
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
