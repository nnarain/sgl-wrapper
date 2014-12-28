
#pragma once

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "SGLExport.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace sgl
{
	struct Quad
	{
		glm::vec2 bottomLeft;
		glm::vec2 topLeft;
		glm::vec2 topRight;
		glm::vec2 bottomRight;
	};

	//! Ray
	struct Ray
	{
		glm::vec3 origin;
		glm::vec3 direction;
	};

	struct Triangle
	{
		glm::vec3 v1;
		glm::vec3 v2;
		glm::vec3 v3;
	};

	struct Line
	{
		glm::vec3 p1;
		glm::vec3 p2;

		Line(glm::vec3 a, glm::vec3 b)
		{
			p1 = a;
			p2 = b;
		}
	};

	namespace util
	{
		SGLVOIDFUNC makeQuad(Quad& quad, float x, float y, float w, float h);
	};
};

#endif
