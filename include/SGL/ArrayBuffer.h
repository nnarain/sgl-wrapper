
#pragma once

#ifndef ARRAYBUFFER_H
#define ARRAYBUFFER_H

#include "SGLExport.h"
#include "IGLBuffer.h"

namespace sgl
{
	SGLCLASS ArrayBuffer
	{
	public:
		ArrayBuffer();
		~ArrayBuffer();

		void bind();
		void unbind();

		void data(void * buffer, int size);
		void subData(void * buffer, int offset, int size);

		void setUsage(GLenum usage);

	private:
		GLuint _id;
		GLenum _usage;

		int _size;

	};
};

#endif
