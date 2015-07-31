
#ifndef RAY_H
#define RAY_H

#include <SGL/Math/Vector3.h>

namespace sgl
{
	struct Ray
	{
		Ray(const Vector3f& o, const Vector3f& d) : origin(o), direction(d)
		{
		}

		Vector3f origin;
		Vector3f direction;
	};
}

#endif
