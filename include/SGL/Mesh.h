
#pragma once

#ifndef SGLMESH_H
#define SGLMESH_H

#include <GL/glew.h>

#include "SGLExport.h"
#include "VertexAttribute.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

#include <vector>

namespace sgl{

	/**
		Encapsulates vertex data for a Mesh
	*/
	SGLCLASS Mesh
	{

	public:

		/**
			@param drawType
				Primitives to draw

			@param drawCount
				number of indices

			@param usage
				Draw usage
		*/
		Mesh(GLenum drawType, int drawCount, VertexBuffer::Usage usage);
		Mesh(void);
		Mesh(const Mesh&);
		Mesh& operator=(const Mesh&);

		~Mesh(void);

		/* Public Functions */
		
		/**
			Create the vertex buffer

			@param data
				buffer of vertices

			@param len
				length of the buffer

			@param stride
				stride between consecutive vertices
		*/
		void create(void *data, int size, int stride);

		/**
			Bind the vertex data
		*/
		void bind();

		/**
			Draw the meshes
		*/
		void draw();

		/**
			Unbind the vertex data
		*/
		void unbind();

		/**
			Add Shader Vertex Attributes
		*/
		void addAttribute(VertexAttribute attrib);

		/**
		*/
		void setDrawType(GLenum);

		/**
		*/
		void setDrawCount(GLint count);

		/**
		*/
		const std::vector<VertexAttribute> &getVertexAttributes() const;

	private:
		//! Handle to Vertex Array Object to save model state
		VertexArray _vao;

		//! Vertex Buffer Object
		VertexBuffer _vbo;

		//! Type of primitive that the mesh is composed of
		GLenum _drawType;
		//! start of data in the buffer
		GLint _drawStart;
		//! number of indices to draw
		GLint _drawCount;
		//! Draw usage
		VertexBuffer::Usage _usage;

		//! is bound flag
		bool _isBound;

		//! List of vertex attributes
		std::vector<VertexAttribute>* _attribs;

		/**
			Calculates the offset in the buffer
		*/
		int offset(int idx);
	};

};

#endif
