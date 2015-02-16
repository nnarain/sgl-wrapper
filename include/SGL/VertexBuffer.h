#ifndef ARRAYBUFFER_H
#define ARRAYBUFFER_H

#include "SGLExport.h"

#include <GL/glew.h>

namespace sgl
{
	SGLCLASS VertexBuffer
	{
	public:
		enum class Usage
		{
			STREAM  = GL_STREAM_DRAW,
			STATIC  = GL_STATIC_DRAW,
			DYNAMIC = GL_DYNAMIC_DRAW
		};

		VertexBuffer();
		VertexBuffer(Usage);
		~VertexBuffer();

		void bind();
		void unbind();

		void data(void * buffer, int size);
		void subData(void * buffer, int offset, int size);

		void setUsage(Usage usage);

	private:
		GLuint _id;
		GLenum _usage;

		int _size;

		void create();
		void destroy();

	};
};

#endif