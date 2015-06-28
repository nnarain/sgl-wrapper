
#include "SGL/Math/AABB.h"

#include <cmath>

using namespace sgl;

AABB::AABB() : AABB(Vector3(0, 0, 0), Vector3(0, 0, 0))
{

}

AABB::AABB(const Vector3& min, const Vector3& max) : min(min), max(max)
{
	center = (this->max + this->min) / 2.0f;

	dim.x = abs(center.x - min.x);
	dim.y = abs(center.y - min.y);
	dim.z = abs(center.z - min.z);
}