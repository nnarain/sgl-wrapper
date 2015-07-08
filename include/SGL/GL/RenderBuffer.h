
#pragma once

#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "SGL/Util/SGLExport.h"

#include <GL/glew.h>

namespace sgl
{
	SGLCLASS RenderBuffer
	{
		NO_COPY(RenderBuffer);

	public:

		enum class Storage
		{
			DEPTH = GL_DEPTH_COMPONENT
		};

		RenderBuffer();
		~RenderBuffer();

		void bind();
		void unbind();

		void storage(Storage component, int w, int h);

		GLuint handle() const;

	private:
		GLuint _id;
	};
};

#endif