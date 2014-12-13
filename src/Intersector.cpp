
#include "SGL/Intersector.h"
#include <glm/geometric.hpp>

using namespace sgl;

bool Intersector::intersectRaySphere(Ray ray, BoundingSphere sphere)
{
	float l = glm::length( glm::cross(ray.direction, sphere.position - ray.origin) );

	if (l <= sphere.radius)
		return true;
	else
		return false;
}

bool Intersector::intersectRayBox(Ray ray, BoundingBox bbox)
{
	float txmin, txmax, tymin, tymax, tzmin, tzmax;

	glm::vec3 bmin = bbox.min();
	glm::vec3 bmax = bbox.max();

	float t0 = glm::length(bmin);
	float t1 = glm::length(bmax);

	if (ray.direction.x >= 0){
		txmin = (bmin.x - ray.origin.x / ray.direction.x);
		txmax = (bmax.x - ray.origin.x / ray.direction.x);
	}
	else{
		txmin = (bmin.x - ray.origin.x / ray.direction.x);
		txmax = (bmax.x - ray.origin.x / ray.direction.x);
	}

	if (ray.direction.y >= 0){
		tymin = (bmin.y - ray.origin.y / ray.direction.y);
		tymax = (bmax.y - ray.origin.y / ray.direction.y);
	}
	else{
		tymin = (bmin.y - ray.origin.y / ray.direction.y);
		tymax = (bmax.y - ray.origin.y / ray.direction.y);
	}

	if ((txmin > tymax) || (tymin > txmax)){
		return false;
	}

	if (tymin > txmin)
		txmin = tymin;

	if (tymax < txmax)
		txmax = tymax;

	if (ray.direction.z >= 0){
		tzmin = (bmin.z - ray.origin.z / ray.direction.z);
		tzmax = (bmax.z - ray.origin.z / ray.direction.z);
	}
	else{
		tzmin = (bmin.z - ray.origin.z / ray.direction.z);
		tzmax = (bmax.z - ray.origin.z / ray.direction.z);
	}

	if ((txmin > tzmax) || (tzmin > txmax))
		return false;

	if (tzmin > txmin)
		txmin = tzmin;

	if (tzmax < txmax)
		txmax = tzmax;

	return ((txmin < t1) && (txmax > t0));
}
