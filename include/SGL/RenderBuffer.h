
#pragma once

#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "SGLExport.h"

#include <GL/glew.h>
#include "IGLBuffer.h"

namespace sgl
{
	SGLCLASS RenderBuffer : public IGLBuffer
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
