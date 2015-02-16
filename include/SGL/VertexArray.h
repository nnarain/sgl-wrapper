
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "SGL/SGLExport.h"

#include <GL/glew.h>

namespace sgl
{
	SGLCLASS VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void bind();
		void unbind();
	private:
		GLuint _id;
	};
}

#endif
