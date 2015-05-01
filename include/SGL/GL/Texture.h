
#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Math/Vector2.h"

#include <GL/glew.h>

namespace sgl{

	/**
		Interface for OpenGL texture
	*/
	SGLCLASS Texture
	{
		NO_COPY(Texture);

	public:
		/* Types */
		
		//! valid texture targets
		enum class Target
		{
			TEXTURE2D = GL_TEXTURE_2D,
			CUBEMAP   = GL_TEXTURE_CUBE_MAP,

			CUBE_MAP_POS_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			CUBE_MAP_NEG_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			CUBE_MAP_POS_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			CUBE_MAP_NEG_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			CUBE_MAP_POS_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			CUBE_MAP_NEG_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};

		//! Texture Format
		enum class Format
		{
			RED       = GL_RED,
			RG        = GL_RG,
			RGB       = GL_RGB,
			BGR       = GL_BGR,
			RGBA      = GL_RGBA,
			BGRA      = GL_BGRA,

			RGBA_DXT1 = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
			RGBA_DXT3 = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
			RGBA_DXT5 = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,

			DEPTH     = GL_DEPTH_COMPONENT
		};

		//! Internal Texture format
		enum class InternalFormat
		{
			RGB   = GL_RGB,
			RGBA  = GL_RGBA,

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
			NEAREST    = GL_NEAREST,
			LINEAR     = GL_LINEAR,
			CLAMP      = GL_CLAMP,
			CLAMP_EDGE = GL_CLAMP_TO_EDGE,
			REPEAT     = GL_REPEAT
		};

		//! Active Texture Unit
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
			T9 = GL_TEXTURE9,

			NONE
		};

		//! Holder for uv coordinates
		struct TextureRegion
		{
			Vector2 bottomLeft;
			Vector2 topLeft;
			Vector2 topRight;
			Vector2 bottomRight;
		};

		/* Constructors */

		Texture(void);
		Texture(Target target, int width, int height, InternalFormat internalFormat, Format format);
		~Texture();

		void setData(char* pixels);
		void setData(Target target, char* pixels);

		void setCompressedData(char * pixels, unsigned int levels, unsigned int blockSize);

		/**
			Bind texture to a texture unit
		*/
		void bind(Unit unit);

		/**
			Bind the texture
		*/
		void bind();

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

		/**
			Create texture region
		*/
		TextureRegion region(float x, float y, float w, float h);

		/*  */

		void setTarget(Target target);
		Texture::Target getTarget() const;

		void setInternalFormat(Texture::InternalFormat);
		InternalFormat getInternalFormat() const;

		void setFormat(Texture::Format);
		Format getFormat() const;

		void setWidth(int w);
		int getWidth() const;

		void setHeight(int h);
		int getHeight() const;

		int getIndex() const;

		GLuint getId() const;

		bool isBound();

	private:
		GLuint _id;

		//! Texture target to bind to
		Target _target;

		//! Current active texture
		Unit _currentUnit;

		//! width of texture
		int _width;
		//! height of texture
		int _height;

		//! internal format of pixel data
		InternalFormat _internalFormat;

		//! format of pixel data
		Format _format;

		//!
		bool _isBound;

		void create();
		void destroy();
	};

};

#endif
