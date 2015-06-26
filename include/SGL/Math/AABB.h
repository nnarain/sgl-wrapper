
#ifndef AABB_H
#define AABB_H

#include "SGL/Util/SGLExport.h"


#include "SGL/Math/Vector3.h"

namespace sgl
{
	SGLCLASS AABB
	{
	public:

		AABB(const Vector3& min, const Vector3& max);

	public:

		Vector3 min;
		Vector3 max;
		Vector3 center;
		Vector3 dim;

	private:
	};
}

#endif
