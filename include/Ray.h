
#pragma once

#ifndef RAY_H
#define RAY_H

#include <glm/vec3.hpp>

namespace sgl{

	struct Ray{
		glm::vec3 origin;
		glm::vec3 direction;

		void setOrigin(float x, float y, float z)
		{
			origin.x = x;
			origin.y = y;
			origin.z = z;
		}

		void setDirection(float x, float y, float z)
		{
			direction.x = x;
			direction.y = y;
			direction.z = z;
		}
	};

};

#endif


