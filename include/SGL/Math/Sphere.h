
#ifndef SPHERE_H
#define SPHERE_H

#include "SGL/Math/Vector3.h"

namespace sgl
{
	struct Sphere
	{
		Vector3 center;
		float radius;

		Sphere() : Sphere(Vector3(0,0,0), 0)
		{
		}

		Sphere(Vector3& c, float r) : center(c), radius(r)
		{
		}
	};
}

#endif
