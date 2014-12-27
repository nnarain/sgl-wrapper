
#pragma once

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "SGLExport.h"

#include <glm/vec2.hpp>

namespace sgl
{
	struct Quad
	{
		glm::vec2 bottomLeft;
		glm::vec2 topLeft;
		glm::vec2 topRight;
		glm::vec2 bottomRight;
	};

	namespace util
	{
		SGLVOIDFUNC makeQuad(Quad& quad, float x, float y, float w, float h);
	};
};

#endif
