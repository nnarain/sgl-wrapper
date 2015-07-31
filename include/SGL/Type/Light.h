
#pragma once

#include "SGL/Math/Vector3.h"

namespace sgl
{
	//! Base structure of lights
	struct BaseLight
	{
		Vector3f color;
		float ambientIntensity;
	};

	//! uniform directional light
	struct DirectionalLight : public BaseLight
	{
		Vector3f direction;
	};

	//! point source light
	struct PointLight : public BaseLight
	{
		Vector3f position;

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
		Vector3f direction;
		float cutoff; ///< angle of spot light spread
	};

}
