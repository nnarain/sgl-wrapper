
#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <GL/glew.h>

namespace sgl{

#ifdef _MSC_VER
	class DLLEXPORT Texture
#else
	class Texture
#endif
	{
	public:
		Texture(void);
		~Texture(void);

		void create(GLint internalFormat, GLenum format, int w, int h, char* pixels);

		void bind(GLuint target);
		void unbind();

		void parameter(GLenum name, GLint param);

		GLuint handle() const;

	private:
		GLuint _id;
	};

};

#endif
