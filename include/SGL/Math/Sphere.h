
#ifndef SPHERE_H
#define SPHERE_H

#include "SGL/Math/Vector3.h"

namespace sgl
{
	struct Sphere
	{
		Vector3 position;
		float radius;

		Sphere(Vector3& p, float r) : position(p), radius(r)
		{
		}
	};
}

#endif
