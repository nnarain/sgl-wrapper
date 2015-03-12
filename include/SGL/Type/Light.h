
#pragma once

#include <glm/glm.hpp>

namespace sgl
{
	//! Base structure of lights
	struct BaseLight
	{
		glm::vec3 color;
		float ambientIntensity;
	};

	//! uniform directional light
	struct DirectionalLight : public BaseLight
	{
		glm::vec3 direction;
	};

	//! point source light
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

	//! cone light
	struct SpotLight : public PointLight
	{
		glm::vec3 direction;
		float cutoff; ///< angle of spot light spread
	};

}
