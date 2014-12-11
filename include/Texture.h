
#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "SGLExport.h"

#include <GL/glew.h>
#include "IGLBuffer.h"

namespace sgl{

	SGLCLASS Texture : public IGLBuffer
	{
	public:
		Texture(int width, int height, GLint internalFormat, GLenum format);
		Texture(GLuint target, int width, int height, GLint internalFormal, GLenum format);
		~Texture(void);

		void data(char* pixels);
		void data(GLuint target, char* pixels);

		void bind(GLuint target);
		void bind();
		void unbind();

		void parameter(GLenum name, GLint param);
		void parameter(GLenum name, GLfloat param);

	private:
		int _width;
		int _height;

		GLint _internalFormat;
		GLenum _format;
	};

};

#endif
