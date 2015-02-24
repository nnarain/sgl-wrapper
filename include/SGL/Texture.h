
#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "SGLExport.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace sgl{

	/**
		Interface for OpenGL texture
	*/
	SGLCLASS Texture
	{
	public:
		/* Types */
		
		//! valid texture targets
		enum class Target
		{
			TEXTURE2D = GL_TEXTURE_2D,
			CUBEMAP   = GL_TEXTURE_CUBE_MAP
		};

		//! Texture Format
		enum class Format
		{
			RED  = GL_RED,
			RG   = GL_RG,
			RGB  = GL_RGB,
			BGR  = GL_BGR,
			RGBA = GL_RGBA,
			BGRA = GL_BGRA
		};

		//! Internal Texture format
		enum class InternalFormat
		{
			RGB = GL_RGB
		};

		//! Texture Parameters
		enum class ParamName
		{
			MAG_FILTER = GL_TEXTURE_MAG_FILTER,
			MIN_FILTER = GL_TEXTURE_MIN_FILTER,
			WRAP_S     = GL_TEXTURE_WRAP_S,
			WRAP_T     = GL_TEXTURE_WRAP_T,
			WRAP_R     = GL_TEXTURE_WRAP_R
		};

		//! Parameter value
		enum class Param
		{
			NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR,
			CLAMP   = GL_CLAMP,
			REPEAT  = GL_REPEAT
		};

		//! Holder for uv coordinates
		struct TextureRegion
		{
			glm::vec2 bottomLeft;
			glm::vec2 topLeft;
			glm::vec2 topRight;
			glm::vec2 bottomRight;
		};

		/* Constructors */

		Texture(Target target, int width, int height, GLint internalFormat, GLenum format);
		~Texture();

		void data(char* pixels);
		void data(GLuint target, char* pixels);

		/**
			Bind texture to a target
		*/
		void bind(GLuint target);

		/**
			Unbind to texture
		*/
		void unbind();

		/**
			Set int parameter of texture
		*/
		void parameter(Texture::ParamName name, Texture::Param param);

		/**
			Set float parameter of texture
		*/
		//void parameter(GLenum name, GLfloat param);

		/**
			Create texture region
		*/
		TextureRegion region(float x, float y, float w, float h);

		/*  */

		void setTarget(Target target);

		GLuint handle();

		bool isBound();

	private:
		GLuint _id;

		GLenum _target;

		//! width of texture
		int _width;
		//! height of texture
		int _height;

		//! internal format of pixel data
		GLint _internalFormat;
		//! format of pixel data
		GLenum _format;

		//!
		bool _isBound;

		void create();
		void destroy();
	};

};

#endif
