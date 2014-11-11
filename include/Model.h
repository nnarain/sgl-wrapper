
#pragma once

#ifndef VERTEXATTRIBUTESET_H
#define VERTEXATTRIBUTESET_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <GL/glew.h>
#include <vector>

#include "VertexAttribute.h"

namespace sgl{

#ifdef _MSC_VER
	class DLLEXPORT Model
#else
	class Model
#endif
	{

	public:

		Model(int drawCount);
		~Model(void);
		
		void create(float *data, int len, int stride);

		void bind();
		void draw();
		void unbind();

		void addAttribute(VertexAttribute *attrib);

	private:
		GLuint _vao;
		GLuint _vbo;

		GLenum _drawType;
		GLint _drawStart;
		GLint _drawCount;

		std::vector<VertexAttribute*>* _attribs;

		int offset(int idx);
	};

};

#endif
