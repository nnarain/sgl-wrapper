
#pragma once

#ifndef INDEXBUFFEROBJECT
#define INDEXBUFFEROBJECT

#include <GL/glew.h>

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

namespace sgl{
#ifdef _MSC_VER
	class DLLEXPORT IndexBufferObject
#else
	class IndexBufferObject
#endif
	{
	public:
		IndexBufferObject(int *indexBuffer, int len);
		~IndexBufferObject();

		void bind();
		int length() const;

	private:
		GLuint _id;
		int _len;

	};
};

#endif
