
#include "SGL/Math/Plane.h"

#include <cmath>

using namespace sgl;

Plane::Plane()
{

}

Plane::Plane(Vector3& p1, Vector3& p2, Vector3& p3)
{
	set(p1, p2, p3);
}

void Plane::set(Vector3& p1, Vector3& p2, Vector3& p3)
{
	Vector3 v1 = Vector3(p1) - p2;
	Vector3 v2 = Vector3(p2) - p3;

	normal.set(v1).cross(v2).normalize();
	d = -normal.dot(p1);
}

float Plane::distanceToPointUnsigned(Vector3& point)
{
	return abs(distanceToPointSigned(point));
}

float Plane::distanceToPointSigned(Vector3& point)
{
	return normal.dot(point) + d;
}

Plane::Side Plane::checkPlaneSide(const Vector3 &point)
{
	float dist = normal.dot(point) + d;

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
