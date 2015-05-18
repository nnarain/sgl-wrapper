
#include "SGL/Math/Plane.h"

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
}

Plane::~Plane()
{

}
