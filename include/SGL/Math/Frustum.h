
#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Math/Plane.h"
#include "SGL/Math/Vector3.h"
#include "SGL/Math/Matrix4.h"
#include "SGL/Math/AABB.h"

namespace sgl
{
	SGLCLASS Frustum
	{
	public:

		enum class Side
		{
			INSIDE, OUTSIDE, INTERSECT
		};

		// planes
		enum class PlaneId
		{
			LEFT, RIGHT,
			TOP, BOTTOM,
			NEAR, FAR
		};

		// points
		enum class PointId
		{
			LBN, LTN, RTN, RBN,
			LBF, LTF, RTF, RBF,

			NC, FC
		};

		Frustum();
		~Frustum();

		Frustum::Side checkPoint(Vector3& point);
		Frustum::Side checkBox(AABB& aabb);

		void construct(float fov, float aspectRatio, float near, float far, const Vector3& pos, const Matrix4& viewMatrix);

		Plane& getPlane(PlaneId id);
		Vector3& getPoint(PointId id);

		float getVolume(void);

	private:
		// left, right, top, bottom, near and far frustum planes
		Plane _planes[6];

		// eight points of the frustum
		Vector3 _points[10];

	};
}

#endif
