
#ifndef GL_TYPES_H
#define GL_TYPES_H

#include <GL/glew.h>

namespace sgl
{
	enum class GLType
	{
		FLOAT  = GL_FLOAT,
		INT	   = GL_INT,
		UINT   = GL_UNSIGNED_INT,
		BYTE   = GL_BYTE,
		UBYTE  = GL_UNSIGNED_BYTE,
		SHORT  = GL_SHORT,
		USHORT = GL_UNSIGNED_SHORT,

		TRUE   = GL_TRUE,
		FALSE  = GL_FALSE
	};
}

#endif
