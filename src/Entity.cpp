#include "Entity.h"
#include <glm/gtx/transform.hpp>

using namespace sgl;

Entity::Entity(void)
{
	pos.w = 1;
	_transformReCalcRequired = true;
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

	_transformReCalcRequired = true;
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

	_transformReCalcRequired = true;
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

	_transformReCalcRequired = true;
}

glm::vec3 Entity::getPosition()
{
	return glm::vec3(pos.x, pos.y, pos.z);
}

glm::mat4 Entity::getRotationMatrix()
{
	glm::mat4 rotateX = glm::rotate(glm::mat4(), angle.x, glm::vec3(1, 0, 0));
	glm::mat4 rotateY = glm::rotate(glm::mat4(), angle.y, glm::vec3(0, 1, 0));
	glm::mat4 rotateZ = glm::rotate(glm::mat4(), angle.z, glm::vec3(0, 0, 1));

	return (rotateX * rotateY * rotateZ);
}

glm::mat4 Entity::getModelMatrix()
{
	if (_transformReCalcRequired){
		glm::mat4 translate = glm::translate(glm::vec3(pos.x, pos.y, pos.z));
		_transform = translate * getRotationMatrix();
		_transformReCalcRequired = false;
	}

	return _transform;
}

glm::mat3 Entity::getNormalMatrix()
{
	return glm::transpose(glm::inverse(glm::mat3(getModelMatrix())));
}

Entity::~Entity(void)
{
}
