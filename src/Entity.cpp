#include "Entity.h"
#include <glm/gtx/transform.hpp>

using namespace sgl;

Entity::Entity(void)
{
	pos.w = 1;
}

void Entity::translate(glm::vec3 t)
{
	translate(t.x, t.y, t.z);
}

void Entity::translate(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
}

void Entity::setPosition(glm::vec3 newPos)
{
	setPosition(newPos.x, newPos.y, newPos.z);
}

void Entity::setPosition(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Entity::rotate(glm::vec3 r)
{
	rotate(r.x, r.y, r.z);
}

void Entity::rotate(float x, float y, float z)
{
	angle.x += x;
	angle.y += y;
	angle.z += z;
}

glm::vec3 Entity::getPosition()
{
	return glm::vec3(pos.x, pos.y, pos.z);
}

glm::mat4 Entity::getModelMatrix()
{
	glm::mat4 translate = glm::translate(glm::vec3(pos.x, pos.y, pos.z));
	glm::mat4 rotateX = glm::rotate(angle.x, glm::vec3(1, 0, 0));
	glm::mat4 rotateY = glm::rotate(angle.y, glm::vec3(0, 1, 0));
	glm::mat4 rotateZ = glm::rotate(angle.z, glm::vec3(0, 0, 1));

	return translate * (rotateX * rotateY * rotateZ);
}

Entity::~Entity(void)
{
}
