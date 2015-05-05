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
			NONE     = GL_NONE,

			COLOR0   = GL_COLOR_ATTACHMENT0,
			COLOR1   = GL_COLOR_ATTACHMENT1,
			COLOR2   = GL_COLOR_ATTACHMENT2,
			COLOR3   = GL_COLOR_ATTACHMENT3,
			COLOR4   = GL_COLOR_ATTACHMENT4,
			COLOR5   = GL_COLOR_ATTACHMENT5,
			COLOR6   = GL_COLOR_ATTACHMENT6,
			COLOR7   = GL_COLOR_ATTACHMENT7,
			COLOR8   = GL_COLOR_ATTACHMENT8,
			COLOR9   = GL_COLOR_ATTACHMENT9,
			COLOR10  = GL_COLOR_ATTACHMENT10,
			COLOR11  = GL_COLOR_ATTACHMENT11,
			COLOR12  = GL_COLOR_ATTACHMENT12,
			COLOR13  = GL_COLOR_ATTACHMENT13,
			COLOR14  = GL_COLOR_ATTACHMENT14,
			COLOR15  = GL_COLOR_ATTACHMENT15,

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
		void setRenderBuffer(RenderBuffer& renderBuffer, Attachment attachment);

		void setDrawBuffer(Attachment a);
		void setDrawBuffers(void);

		void addAttachment(Attachment attachment);

		bool error();

		GLuint getId() const;

	private:
		GLuint _id;
		Target _target;

		std::vector<GLenum>* _attachments;
	};

};

#endif