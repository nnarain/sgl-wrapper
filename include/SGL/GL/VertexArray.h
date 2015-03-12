
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "SGL/Util/SGLExport.h"

#include <GL/glew.h>

namespace sgl
{
	SGLCLASS VertexArray
	{
		NO_COPY(VertexArray);

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
