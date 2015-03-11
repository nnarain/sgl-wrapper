#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "SGL/Util/SGLExport.h"

#include <GL/glew.h>
#include <vector>

#include "SGL/GL/Texture.h"
#include "SGL/GL/RenderBuffer.h"

namespace sgl
{
	SGLCLASS FrameBuffer
	{
		NO_COPY(FrameBuffer);

	public:
		/* Types */

		enum class Target
		{
			DEFAULT = GL_FRAMEBUFFER,
			READ    = GL_READ_FRAMEBUFFER,
			DRAW    = GL_DRAW_FRAMEBUFFER
		};

		enum class Attachment
		{
			COLOR0   = GL_COLOR_ATTACHMENT0,
			DEPTH    = GL_DEPTH_ATTACHMENT,
			STENCIL  = GL_STENCIL_ATTACHMENT
		};

		FrameBuffer();
		~FrameBuffer();

		void bind(Target);
		void bind();
		void unbind();

		void setTexture(Texture& texture, Attachment attachment);
		void setTexture2D(const Texture &texture, Attachment attachment);
		void setRenderBuffer(RenderBuffer& renderBuffer, GLuint attachment);

		void setDrawBuffer();

		void addAttachment(GLenum attachment);

		bool error();

		GLuint getId() const;

	private:
		GLuint _id;
		Target _target;

		std::vector<GLenum>* _attachments;
	};

};

#endif