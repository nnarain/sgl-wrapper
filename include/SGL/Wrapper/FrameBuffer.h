#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "SGL/Util/SGLExport.h"

#include <GL/glew.h>
#include <vector>

#include "SGL/Wrapper/Texture.h"
#include "SGL/Wrapper/RenderBuffer.h"

namespace sgl
{
	SGLCLASS FrameBuffer
	{
	public:
		/* Types */

		enum class Mode
		{
			DEFAULT = GL_FRAMEBUFFER,
			READ    = GL_READ_FRAMEBUFFER,
			DRAW    = GL_DRAW_FRAMEBUFFER
		};

		FrameBuffer();
		~FrameBuffer();

		void bind(Mode);
		void bind();
		void unbind();

		void setTexture(Texture& texture, GLuint attachment);
		void setRenderBuffer(RenderBuffer& renderBuffer, GLuint attachment);

		void setDrawBuffer();

		void addAttachment(GLenum attachment);

	private:
		GLuint _id;
		GLuint _target;

		std::vector<GLenum>* _attachments;

		bool error();
	};

};

#endif