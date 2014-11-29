
#pragma once

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <GL/glew.h>
#include <vector>

#include "IGLBuffer.h"
#include "Texture.h"
#include "RenderBuffer.h"

namespace sgl
{

#ifdef _MSC_VER
	class DLLEXPORT FrameBuffer
#else
	class FrameBuffer
#endif
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
		std::vector<GLenum> _attachments;

		bool error();
	};

};

#endif
