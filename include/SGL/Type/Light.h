
#pragma once

#include "SGL/Math/Vector3.h"

namespace sgl
{
	//! Base structure of lights
	struct BaseLight
	{
		Vector3 color;
		float ambientIntensity;
	};

	//! uniform directional light
	struct DirectionalLight : public BaseLight
	{
		Vector3 direction;
	};

	//! point source light
	struct PointLight : public BaseLight
	{
		Vector3 position;

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
		Vector3 direction;
		float cutoff; ///< angle of spot light spread
	};

}
