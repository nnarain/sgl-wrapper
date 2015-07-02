
#ifndef RAY_H
#define RAY_H

#include <SGL/Math/Vector3.h>

namespace sgl
{
	struct Ray
	{
		Ray(const Vector3& o, const Vector3& d) : origin(o), direction(d)
		{
		}

		Vector3 origin;
		Vector3 direction;
	};
}

#endif
