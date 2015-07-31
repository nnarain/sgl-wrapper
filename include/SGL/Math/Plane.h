
#ifndef PLANE_H
#define PLANE_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Math/Vector3.h"

namespace sgl
{
	SGLCLASS Plane
	{
	public:

		enum class Side
		{
			BACK, FRONT, ON
		};

		Plane(Vector3f& p1, Vector3f& p2, Vector3f& p3);
		Plane();
		~Plane();

		void set(Vector3f& p1, Vector3f& p2, Vector3f& p3);

		float distanceToPointUnsigned(Vector3f& point);
		float distanceToPointSigned(Vector3f& point);

		Plane::Side checkPlaneSide(const Vector3f &point);

	public:
		// the planes normal
		Vector3f normal;

		// the plane constant
		float d;

	private:
	};
}

#endif
