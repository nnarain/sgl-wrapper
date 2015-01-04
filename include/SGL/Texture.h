
#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "SGLExport.h"

#include <GL/glew.h>
#include "IGLBuffer.h"

#include <glm/vec2.hpp>

namespace sgl{

	/**
		Interface for OpenGL texture
	*/
	SGLCLASS Texture : public IGLBuffer
	{
	public:
		/* Types */

		//! Holder for uv coordinates
		struct TextureRegion
		{
			glm::vec2 bottomLeft;
			glm::vec2 topLeft;
			glm::vec2 topRight;
			glm::vec2 bottomRight;
		};

		/* Constructors */

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

		/**
			Create texture region
		*/
		TextureRegion region(float x, float y, float w, float h);

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
