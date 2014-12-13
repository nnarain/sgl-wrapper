
#pragma once

#ifndef MODEL_H
#define MODEL_H

#include "SGLExport.h"

#include <GL/glew.h>
#include <vector>

#include "ShaderProgram.h"
#include "VertexAttribute.h"

namespace sgl{

	/**
		Encapsulates vertex data for a Model
	*/
	SGLCLASS Model
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
		Model(GLenum drawType, int drawCount, GLenum usage);
		~Model(void);
		
		/**
			Create the vertex buffer

			@param data
				buffer of vertices

			@param len
				length of the buffer

			@param stride
				stride between consecutive vertices
		*/
		void create(float *data, int len, int stride);

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

		void addAttribute(ShaderProgram& shader, std::string name);

	private:
		//! Handle to Vertex Array Object to save model state
		GLuint _vao;
		//! Handle to Vertex Buffer Object 
		GLuint _vbo;

		//! Type of primitive that the mesh is composed of
		GLenum _drawType;
		//! start of data in the buffer
		GLint _drawStart;
		//! number of indices to draw
		GLint _drawCount;
		//! Draw usage
		GLenum _usage;

		//! List of vertex attributes
		std::vector<VertexAttribute>* _attribs;

		/**
			Calculates the offset in the buffer
		*/
		int offset(int idx);
	};

};

#endif
