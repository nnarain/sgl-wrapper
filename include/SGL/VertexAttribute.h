
#pragma once

#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

#include <GL/glew.h>

namespace sgl
{
	//! Represent a vertex attribute in a shader and model data
	struct VertexAttribute
	{
		GLuint loc;
		int numComponents;
	};
};

#endif
