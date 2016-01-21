
#ifndef SPHERE_H
#define SPHERE_H

#include "SGL/Math/Vector3.h"

namespace sgl
{
	struct Sphere
	{
		Vector3f center;
		float radius;

		Sphere() : Sphere(Vector3f(0,0,0), 0)
		{
		}

		Sphere(Vector3f& c, float r) : center(c), radius(r)
		{
		}
	};
}

#endif
