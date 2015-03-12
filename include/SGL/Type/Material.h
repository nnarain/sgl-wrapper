
#pragma once

#include <glm/glm.hpp>

namespace sgl
{
	struct Material
	{
		glm::vec3 ambientColor;

		glm::vec3 diffuseColor;
		float diffuseIntensity;

		glm::vec3 specularColor;
		float specularIntensity;
		float specularPower;
	};
}
