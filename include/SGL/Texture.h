
#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "SGLExport.h"

#include <GL/glew.h>
#include "IGLBuffer.h"

namespace sgl{

	/**
		Interface for OpenGL texture
	*/
	SGLCLASS Texture : public IGLBuffer
	{
	public:
		Texture(int width, int height, GLint internalFormat, GLenum format);
		Texture(GLuint target, int width, int height, GLint internalFormal, GLenum format);
		~Texture(void);

		void data(char* pixels);
		void data(GLuint target, char* pixels);

		/**
			Bind texture to a target
		*/
		void bind(GLuint target);

		/**
			Bind to the default target
		*/
		void bind();

		/**
			Unbind to texture
		*/
		void unbind();

		/**
			Set int parameter of texture
		*/
		void parameter(GLenum name, GLint param);

		/**
			Set float parameter of texture
		*/
		void parameter(GLenum name, GLfloat param);

	private:
		//! width of texture
		int _width;
		//! height of texture
		int _height;

		//! internal format of pixel data
		GLint _internalFormat;
		//! format of pixel data
		GLenum _format;
	};

};

#endif
