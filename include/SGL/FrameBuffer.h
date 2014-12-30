
#pragma once

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "SGLExport.h"

#include <GL/glew.h>
#include <vector>

#include "IGLBuffer.h"
#include "Texture.h"
#include "RenderBuffer.h"

namespace sgl
{
	SGLCLASS FrameBuffer
		: public IGLBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		void bind(GLuint target);
		void bind();
		void unbind();

		void setTexture(Texture& texture, GLuint attachment);
		void setRenderBuffer(RenderBuffer& renderBuffer, GLuint attachment);

		void setDrawBuffer();

		void addAttachment(GLenum attachment);

	private:
		std::vector<GLenum>* _attachments;

		bool error();
	};

};

#endif
