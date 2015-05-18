
#ifndef PLANE_H
#define PLANE_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Math/Vector3.h"

namespace sgl
{
	SGLCLASS Plane
	{
	public:

		Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3);
		Plane();
		~Plane();

		void set(const Vector3& p1, const Vector3& p2, const Vector3& p3);

	private:
		// the planes normal
		Vector3 _normal;
		// the plane constant
		float _d;
	};
}

#endif
