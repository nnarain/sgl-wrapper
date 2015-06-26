
#include "SGL/Math/AABB.h"

using namespace sgl;

AABB::AABB(const Vector3& min, const Vector3& max) : min(min), max(max)
{
	center = (this->max + this->min) / 2.0f;
}