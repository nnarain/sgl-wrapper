
#ifndef AABB_H
#define AABB_H

#include "SGL/Util/SGLExport.h"


#include "SGL/Math/Vector3.h"

namespace sgl
{
	SGLCLASS AABB
	{
	public:

		AABB();
		AABB(const Vector3f& min, const Vector3f& max);

	public:

		Vector3f min;
		Vector3f max;
		Vector3f center;
		Vector3f dim;

	private:
	};
}

#endif
