
#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Math/Plane.h"
#include "SGL/Math/Vector3.h"

namespace sgl
{
	SGLCLASS Frustum
	{
	public:

		// planes
		enum class PlaneId
		{
			LEFT, RIGHT,
			TOP, BOTTOM,
			NEAR, FAR
		};

		Frustum();
		~Frustum();

		Plane& getPlane(PlaneId id);

	private:
		// left, right, top, bottom, near and far frustum planes
		Plane _planes[6];

	};
}

#endif
