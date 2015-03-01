
#pragma once

#include <glm/glm.hpp>

namespace sgl
{
	struct BaseLight
	{
		glm::vec3 color;
		float ambientIntensity;
	};

	struct DirectionalLight : public BaseLight
	{
		glm::vec3 direction;
	};

	struct PointLight : public BaseLight
	{
		glm::vec3 position;

		struct
		{
			float c;
			float l;
			float e;
		}atten;
	};
}
