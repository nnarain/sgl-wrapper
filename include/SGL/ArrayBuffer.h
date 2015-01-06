
#pragma once

#ifndef ARRAYBUFFER_H
#define ARRAYBUFFER_H

#include "SGLExport.h"
#include "IGLBuffer.h"

namespace sgl
{
	SGLCLASS ArrayBuffer : public IGLBuffer
	{
	public:
		ArrayBuffer();
		~ArrayBuffer();

		void bind();
		void unbind();

		void data(void * buffer, int size);

		void setUsage(GLenum usage);

	private:
		GLenum _usage;

		int _size;

	};
};

#endif
