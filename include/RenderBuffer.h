
#pragma once

#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <GL/glew.h>

namespace sgl
{
#ifdef _MSC_VER
	class DLLEXPORT RenderBuffer
#else
	class RenderBuffer
#endif
	{
	public:
		RenderBuffer();
		~RenderBuffer();

		void bind(GLuint target);
		void unbind(GLuint target);

		void storage(GLuint component, int w, int h);

		GLuint handle() const;

	private:
		GLuint _rbo;
	};
};

#endif
