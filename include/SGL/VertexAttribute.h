
#pragma once

#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

#include <GL/glew.h>

namespace sgl
{
	//! Represent a vertex attribute in a shader and model data
	struct VertexAttribute
	{
		//! Shader location of attribute
		GLuint loc;
		//! number of components inthe attributes
		int numComponents;

		VertexAttribute()
		{
		}

		VertexAttribute(GLuint l, int n)
		{
			loc = l;
			numComponents = n;
		}
	};

	//!
	struct InstancedVertexAttriute
	{
		GLuint loc;
		int size;

		InstancedVertexAttriute(GLuint l, int s)
		{
			loc = l;
			size = s;
		}
	};
};

#endif
