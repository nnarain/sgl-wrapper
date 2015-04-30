
#pragma once

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Math/Vector2.h"
#include "SGL/Math/Vector3.h"

#include <glm/glm.hpp>

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
		Vector3 origin;
		Vector3 direction;
	};

	namespace util
	{
		SGLVOIDFUNC makeQuad(Quad& quad, float x, float y, float w, float h);
	};
};

#endif
