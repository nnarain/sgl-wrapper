
#pragma once

#ifndef MODEL_H
#define MODEL_H

#include "SGLExport.h"

#include <GL/glew.h>
#include <vector>

#include "ShaderProgram.h"

namespace sgl{

	SGLCLASS Model
	{

	public:

		struct VertexAttribute_t{
			GLuint loc;
			int numComponents;
		};

		Model(int drawCount);
		~Model(void);
		
		void create(float *data, int len, int stride);

		void bind();
		void draw();
		void unbind();

		void addAttribute(ShaderProgram& shader, std::string name, int numComponents);

	private:
		GLuint _vao;
		GLuint _vbo;

		GLenum _drawType;
		GLint _drawStart;
		GLint _drawCount;

		std::vector<VertexAttribute_t>* _attribs;

		int offset(int idx);
	};

};

#endif
