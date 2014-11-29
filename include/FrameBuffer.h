
#pragma once

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <GL/glew.h>
#include <vector>

#include "Texture.h"
#include "RenderBuffer.h"

namespace sgl
{

#ifdef _MSC_VER
	class DLLEXPORT FrameBuffer
#else
	class FrameBuffer
#endif
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		void bind(GLuint target);
		void unbind(GLuint target);

		void setTexture(Texture& texture, GLuint attachment);
		void setRenderBuffer(RenderBuffer& renderBuffer, GLuint attachment);

		void setDrawBuffer();

		void addAttachment(GLenum attachment);

	private:
		GLuint _fbo;

		std::vector<GLenum> _attachments;

		bool error();
	};

};

#endif
