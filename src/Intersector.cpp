
#include "Intersector.h"
#include <glm/geometric.hpp>

using namespace sgl;

bool Intersector::raysphere(Ray ray, BoundingSphere sphere)
{
	float l = glm::length( glm::cross(ray.direction, sphere.getPosition() - ray.origin) );

	if (l <= sphere.radius())
		return true;
	else
		return false;
}
