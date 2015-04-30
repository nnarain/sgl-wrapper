#include "SGL/Util/Entity.h"
#include <glm/gtx/transform.hpp>

#include <algorithm>

using namespace sgl;

Entity::Entity(void)
{
}

void Entity::translate(const Vector3& t)
{
	translate(t.x, t.y, t.z);
}

void Entity::translate(float x, float y, float z)
{

}

void Entity::setPosition(const Vector3& newPos)
{
	setPosition(newPos.x, newPos.y, newPos.z);
}

void Entity::setPosition(float x, float y, float z)
{

}

void Entity::rotate(const Vector3& r)
{
	rotate(r.x, r.y, r.z);
}

void Entity::rotate(float x, float y, float z)
{

}

void Entity::scale(const Vector3& s)
{
	scale(s.x, s.y, s.z);
}

void Entity::scale(float x, float y, float z)
{

}

void Entity::scale(float t)
{
	scale(t, t, t);
}

Entity::~Entity(void)
{
}
