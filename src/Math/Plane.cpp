
#include "SGL/Math/Plane.h"

#include <cmath>

using namespace sgl;

Plane::Plane()
{

}

Plane::Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3)
{
	set(p1, p2, p3);
}

void Plane::set(const Vector3& p1, const Vector3& p2, const Vector3& p3)
{
	Vector3 v1 = Vector3(p1) - p2;
	Vector3 v2 = Vector3(p2) - p3;

	_normal.set(v1).cross(v2).normalize();
	_d = -(_normal.dot(p1));

	ref = p1;
}

float Plane::distanceToPointUnsigned(Vector3& point)
{
	return abs(_normal.dot(point));
}

float Plane::distanceToPointSigned(Vector3& point)
{
	return _normal.dot(point);
}

Plane::Side Plane::checkPlaneSide(const Vector3 &point)
{
	float dist = _normal.dot(point) + _d;

	if (dist == 0)
	{
		return Plane::Side::ON;
	}
	else if (dist < 0)
	{
		return Plane::Side::BACK;
	}
	else
	{
		return Plane::Side::FRONT;
	}
}

Plane::~Plane()
{

}
