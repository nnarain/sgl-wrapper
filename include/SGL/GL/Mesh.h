
#pragma once

#ifndef SGLMESH_H
#define SGLMESH_H

#include <GL/glew.h>

#include "SGL/Util/SGLExport.h"
#include "SGL/GL/VertexAttribute.h"
#include "SGL/GL/Buffer.h"
#include "SGL/GL/VertexArray.h"

#include <vector>

namespace sgl{

	/**
		Encapsulates vertex data for a Mesh
	*/
	SGLCLASS Mesh
	{
		NO_COPY(Mesh);

	public:

		//! Draw Types
		enum class Type
		{
			POINTS                   = GL_POINTS,
			LINE_STRIP               = GL_LINE_STRIP,
			LINE_LOOP                = GL_LINE_LOOP,
			LINES                    = GL_LINES,
			LINE_STRIP_ADJACENCY     = GL_LINE_STRIP_ADJACENCY,
			LINES_ADJACENCY          = GL_LINES_ADJACENCY,
			TRIANGLES_STRIP          = GL_TRIANGLE_STRIP,
			TRIANGLE_FAN             = GL_TRIANGLE_FAN,
			TRIANGLES                = GL_TRIANGLES,
			TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
			TRIANGLES_ADJACENCY      = GL_TRIANGLES_ADJACENCY
		};

		/**
			@param drawType
				Primitives to draw

			@param drawCount
				number of indices

			@param usage
				Draw usage
		*/
		Mesh(Type type, Buffer::Usage usage);
		Mesh(Type type, int drawCount, Buffer::Usage usage);
		Mesh(void);

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
		void create(int stride);

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
		void setDrawType(Type);

		/**
		*/
		void setDrawCount(GLint count);

		/**
		*/
		void setDrawStart(GLint start);

		/**
		*/
		Buffer &getVBO();

		/**
		*/
		const std::vector<VertexAttribute> &getVertexAttributes() const;

	private:
		//! Handle to Vertex Array Object to save model state
		VertexArray _vao;

		//! Vertex Buffer Object
		Buffer _vbo;

		//! Type of primitive that the mesh is composed of
		Type _drawType;
		//! start of data in the buffer
		GLint _drawStart;
		//! number of indices to draw
		GLint _drawCount;
		//! Draw usage
		Buffer::Usage _usage;

		//! is bound flag
		bool _isBound;

		//! List of vertex attributes
		std::vector<VertexAttribute>* _attribs;


		/**/

		/**
			@return the size in bytes of the given data type constant
		*/
		unsigned int dataTypeSize(GLType);
	};

};

#endif
