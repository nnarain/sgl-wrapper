
#pragma once

#include "SGL/Math/Vector3.h"

namespace sgl
{
	struct Material
	{
		Vector3 ambientColor;

		Vector3 diffuseColor;
		float diffuseIntensity;

		Vector3 specularColor;
		float specularIntensity;
		float specularPower;
	};
}
