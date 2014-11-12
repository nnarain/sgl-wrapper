
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

		void create();

		void bind();
		void unbind();

	private:
		GLuint _id;
	};

};

#endif
