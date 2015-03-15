
#pragma once

#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

#include <GL/glew.h>

#include "SGL/Type/GLTypes.h"

namespace sgl
{
	//! Represent a vertex attribute in a shader and model data
	struct VertexAttribute
	{
		//! Shader location of attribute
		GLuint loc;

		//! number of components inthe attributes
		int numComponents;

		//! Attribute Data Type
		GLType type;

		//
		VertexAttribute(GLuint l, int n, GLType t) :
			loc(l),
			numComponents(n),
			type(t)
		{
		}

		VertexAttribute(GLuint l, int n) : VertexAttribute(l, n, GLType::FLOAT)
		{
		}
	};


};

#endif
