
#include "SGL/Math/Frustum.h"

#include "SGL/Math/MathUtil.h"

//LBN, LTN, RTN, RBN,
//LBF, LTF, RTF, RBF

using namespace sgl;

Frustum::Frustum()
{
}


void Frustum::construct(float fov, float aspectRatio, float near, float far, const Vector3& pos, const Matrix4& viewMatrix)
{
	// near plane height
	float nearH = 2 * tanDeg(fov / 2.0f) * near;
	// near plane width
	float nearW = nearH * aspectRatio;

	// far plane height
	float farH = 2 * tanDeg(fov / 2.0f) * far;
	// far plane width
	float farW = farH * aspectRatio;

	// extracted right vector
	Vector3 right;
	right.x = viewMatrix[0][0];
	right.y = viewMatrix[1][0];
	right.z = viewMatrix[2][0];

	// extracted up vector
	Vector3 up;
	up.x = viewMatrix[0][1];
	up.y = viewMatrix[1][1];
	up.z = viewMatrix[2][1];

	// extracted forward vector
	Vector3 forward;
	forward.x = -viewMatrix[0][2];
	forward.y = -viewMatrix[1][2];
	forward.z = -viewMatrix[2][2];

	// near plane center point
	Vector3 nearCenter = Vector3(pos) + (forward * near);

	// far plane center point
	Vector3 farCenter  = Vector3(pos) + (forward * far);

	//
	Vector3& ltn = getPoint(PointId::LTN);
	ltn = nearCenter + (up * nearH / 2.0f) - (right * nearW / 2.0f);

	Vector3& lbn = getPoint(PointId::LBN);
	lbn = nearCenter - (up * nearH / 2.0f) - (right * nearW / 2.0f);

	Vector3& rtn = getPoint(PointId::RTN);
	rtn = nearCenter + (up * nearH / 2.0f) + (right * nearW / 2.0f);

	Vector3& rbn = getPoint(PointId::RBN);
	rbn = nearCenter - (up * nearH / 2.0f) + (right * nearW / 2.0f);

	Vector3& ltf = getPoint(PointId::LTF);
	ltf = nearCenter + (up * farH / 2.0f) - (right * farW / 2.0f);

	Vector3& lbf = getPoint(PointId::LBF);
	lbf = nearCenter - (up * farH / 2.0f) - (right * farW / 2.0f);

	Vector3& rtf = getPoint(PointId::RTF);
	rtf = nearCenter + (up * farH / 2.0f) + (right * farW / 2.0f);

	Vector3& rbf = getPoint(PointId::RBF);
	rbf = nearCenter - (up * farH / 2.0f) + (right * farW / 2.0f);
}

Plane& Frustum::getPlane(PlaneId id)
{
	return _planes[static_cast<int>(id)];
}

Vector3& Frustum::getPoint(PointId id)
{
	return _points[static_cast<int>(id)];
}

Frustum::~Frustum()
{

}
