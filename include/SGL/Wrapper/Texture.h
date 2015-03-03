
#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "SGL/Util/SGLExport.h"

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
			RED   = GL_RED,
			RG    = GL_RG,
			RGB   = GL_RGB,
			BGR   = GL_BGR,
			RGBA  = GL_RGBA,
			BGRA  = GL_BGRA,

			DEPTH = GL_DEPTH_COMPONENT
		};

		//! Internal Texture format
		enum class InternalFormat
		{
			RGB   = GL_RGB,

			DEPTH = GL_DEPTH_COMPONENT
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
			LINEAR  = GL_LINEAR,
			CLAMP   = GL_CLAMP,
			REPEAT  = GL_REPEAT
		};

		enum class Unit
		{
			T0 = GL_TEXTURE0,
			T1 = GL_TEXTURE1,
			T2 = GL_TEXTURE2,
			T3 = GL_TEXTURE3,
			T4 = GL_TEXTURE4,
			T5 = GL_TEXTURE5,
			T6 = GL_TEXTURE6,
			T7 = GL_TEXTURE7,
			T8 = GL_TEXTURE8,
			T9 = GL_TEXTURE9
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

		Texture(Target target, int width, int height, InternalFormat internalFormat, Format format);
		~Texture();

		void data(char* pixels);
		void data(Target target, char* pixels);

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
		Texture::Target getTarget() const;

		GLuint getId() const;

		bool isBound();

	private:
		GLuint _id;

		Target _target;

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
