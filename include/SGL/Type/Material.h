
#pragma once

#include "SGL/Math/Vector3.h"

namespace sgl
{
	struct Material
	{
		Vector3f ambientColor;

		Vector3f diffuseColor;
		float diffuseIntensity;

		Vector3f specularColor;
		float specularIntensity;
		float specularPower;
	};
}
