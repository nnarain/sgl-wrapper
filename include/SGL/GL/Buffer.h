#ifndef ARRAYBUFFER_H
#define ARRAYBUFFER_H

#include "SGL/Util/SGLExport.h"

#include <GL/glew.h>

namespace sgl
{
	/**
		Wrapper around OpenGL Buffer Object

		The default constructor produces a GL_STATIC_DRAW GL_ARRAY_BUFFER
	*/
	SGLCLASS Buffer
	{
		NO_COPY(Buffer);

	public:
		//! Valid Target
		enum class Target
		{
			ARRAY              = GL_ARRAY_BUFFER,
			ATOMIC_COUNTER     = GL_ATOMIC_COUNTER_BUFFER,
			COPY_READ          = GL_COPY_READ_BUFFER,
			COPY_WRITE         = GL_COPY_WRITE_BUFFER,
			DRAW_INDIRECT      = GL_DRAW_INDIRECT_BUFFER,
			DISPATCH_INDIRECT  = GL_DISPATCH_INDIRECT_BUFFER,
			ELEMENT            = GL_ELEMENT_ARRAY_BUFFER,
			PIXEL_PACK         = GL_PIXEL_PACK_BUFFER,
			PIXEL_UNPACK       = GL_PIXEL_UNPACK_BUFFER,
			QUERY              = GL_QUERY_BUFFER,
			SHADER_STORAGE     = GL_SHADER_STORAGE_BUFFER,
			TEXTURE            = GL_TEXTURE_BUFFER,
			TRANSFORM_FEEDBACK = GL_TRANSFORM_FEEDBACK_BUFFER,
			UNIFORM            = GL_UNIFORM_BUFFER
		};

		//! Valid Usages
		enum class Usage
		{
			STREAM_DRAW  = GL_STREAM_DRAW,
			STREAM_READ  = GL_STREAM_READ,
			STREAM_COPY  = GL_STREAM_COPY,
			STATIC_DRAW  = GL_STATIC_DRAW,
			STATIC_READ  = GL_STATIC_READ,
			STATIC_COPY  = GL_STATIC_COPY,
			DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
			DYNAMIC_READ = GL_DYNAMIC_READ,
			DYANMIC_COPY = GL_DYNAMIC_COPY
		};

		/**
			Create a static array buffer
		*/
		Buffer();

		/**
		*/
		Buffer(Target target, Usage usage);
		~Buffer();

	public:

		void bind();
		void unbind();

		void setData(void * buffer, int size);

		void subData(void * buffer, int offset, int size);

		void setTarget(Target);
		void setUsage(Usage);

		GLuint getId() const;

	private:
		GLuint _id;

		GLenum _target;
		GLenum _usage;

		int _size;

		void create();
		void destroy();
	};
};

#endif