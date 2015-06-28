
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

		Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3);
		Plane();
		~Plane();

		void set(const Vector3& p1, const Vector3& p2, const Vector3& p3);

		float distanceToPointUnsigned(Vector3& point);
		float distanceToPointSigned(Vector3& point);

		Plane::Side checkPlaneSide(const Vector3 &point);

	public:
		// the planes normal
		Vector3 normal;

		// the plane constant
		float d;

	private:
	};
}

#endif
