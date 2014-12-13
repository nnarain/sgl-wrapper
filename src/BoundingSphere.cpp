
#include "SGL/Geometry.h"

#include <glm/geometric.hpp>
#include <cstdlib>

using namespace sgl;

BoundingSphere::BoundingSphere(float r, float x, float y, float z) : BoundingSphere(r, glm::vec3(x,y,z))
{
}

BoundingSphere::BoundingSphere(float r, glm::vec3 pos)
{
	radius = r;
	position = pos;
}

BoundingSphere BoundingSphere::create(glm::vec3* vertices, int size)
{
	qsort(vertices, size, sizeof(glm::vec3), compare);

	glm::vec3 largest = vertices[size - 1];

	return BoundingSphere(glm::length(largest), 0, 0, 0);
}

int BoundingSphere::compare(const void* a, const void* b)
{
	glm::vec3 u = *(glm::vec3*) a;
	glm::vec3 v = *(glm::vec3*) b;

	float ul = glm::length(u);
	float vl = glm::length(v);

	if (ul < vl)  return -1;
	if (ul == vl) return 0;
	if (ul > vl)  return 1;
}

BoundingSphere::~BoundingSphere()
{
}
