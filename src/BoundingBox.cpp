
#include "SGL/Geometry.h"

#include <cstdlib>
#include <glm/geometric.hpp>

using namespace sgl;

BoundingBox::BoundingBox() : BoundingBox(glm::vec3(0, 0, 0), glm::vec3(0,0,0))
{
}

BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max)
{
	_min = min;
	_max = max;
}

glm::vec3 BoundingBox::min() const
{
	return _min;
}

glm::vec3 BoundingBox::max() const
{
	return _max;
}

glm::vec3 BoundingBox::center() const
{
	return (_max - _min) / 2.0f;
}

void BoundingBox::transform(glm::mat4 transform)
{
	glm::vec4 tMin = glm::vec4(_min, 1);
	tMin = transform * tMin;

	_min = glm::vec3(tMin);

	glm::vec4 tMax = glm::vec4(_max, 1);
	tMax = transform * tMax;

	_max = glm::vec3(tMax);
}

/* Quick Sort Compare Functions */

BoundingBox BoundingBox::create(glm::vec3* vertices, int size)
{
	qsort(vertices, size, sizeof(glm::vec3), compareX);
	qsort(vertices, size, sizeof(glm::vec3), compareY);
	qsort(vertices, size, sizeof(glm::vec3), compareZ);

	glm::vec3 min = vertices[0];
	glm::vec3 max = vertices[size - 1];

	return BoundingBox(min, max);
}

int BoundingBox::compareX(const void* a, const void* b)
{
	glm::vec3 u = *((glm::vec3*)a);
	glm::vec3 v = *((glm::vec3*)b);

	if (u.x < v.x)  return -1;
	if (u.x == v.x) return 0;
	if (u.x > v.x)  return 1;
}

int BoundingBox::compareY(const void* a, const void* b)
{
	glm::vec3 u = *((glm::vec3*)a);
	glm::vec3 v = *((glm::vec3*)b);

	if (u.y < v.y)  return -1;
	if (u.y == v.y) return 0;
	if (u.y > v.y)  return 1;
}

int BoundingBox::compareZ(const void* a, const void* b)
{
	glm::vec3 u = *((glm::vec3*)a);
	glm::vec3 v = *((glm::vec3*)b);

	if (u.z < v.z)  return -1;
	if (u.z == v.z) return 0;
	if (u.z > v.z)  return 1;
}

BoundingBox::~BoundingBox()
{
}
