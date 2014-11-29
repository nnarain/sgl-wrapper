
#pragma once

#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <GL/glew.h>
#include "IGLBuffer.h"

namespace sgl
{
#ifdef _MSC_VER
	class DLLEXPORT RenderBuffer
#else
	class RenderBuffer
#endif
		: public IGLBuffer
	{
	public:
		RenderBuffer();
		~RenderBuffer();

		void bind(GLuint target);
		void bind();
		void unbind();

		void storage(GLuint component, int w, int h);

	};
};

#endif
