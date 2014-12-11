#include "Entity.h"
#include <glm/gtx/transform.hpp>

using namespace sgl;

Entity::Entity(void)
{
	_pos.w = 1;

	_scale = glm::vec3(1, 1, 1);

	_transformReCalcRequired = true;
}

void Entity::translate(glm::vec3 t)
{
	translate(t.x, t.y, t.z);
}

void Entity::translate(float x, float y, float z)
{
	_pos.x += x;
	_pos.y += y;
	_pos.z += z;

	_transformReCalcRequired = true;
}

void Entity::setPosition(glm::vec3 newPos)
{
	setPosition(newPos.x, newPos.y, newPos.z);
}

void Entity::setPosition(float x, float y, float z)
{
	_pos.x = x;
	_pos.y = y;
	_pos.z = z;

	_transformReCalcRequired = true;
}

void Entity::rotate(glm::vec3 r)
{
	rotate(r.x, r.y, r.z);
}

void Entity::rotate(float x, float y, float z)
{
	_angle.x += x;
	_angle.y += y;
	_angle.z += z;

	_transformReCalcRequired = true;
}

void Entity::scale(glm::vec3 s)
{
	scale(s.x, s.y, s.z);
}

void Entity::scale(float x, float y, float z)
{
	_scale.x *= x;
	_scale.y *= y;
	_scale.z *= z;
}

void Entity::scale(float t)
{
	scale(t, t, t);
}

glm::vec3 Entity::getPosition()
{
	return glm::vec3(_pos.x, _pos.y, _pos.z);
}

glm::mat4 Entity::getRotationMatrix()
{
	glm::mat4 rotateX = glm::rotate(glm::mat4(), _angle.x, glm::vec3(1, 0, 0));
	glm::mat4 rotateY = glm::rotate(glm::mat4(), _angle.y, glm::vec3(0, 1, 0));
	glm::mat4 rotateZ = glm::rotate(glm::mat4(), _angle.z, glm::vec3(0, 0, 1));

	return (rotateX * rotateY * rotateZ);
}

glm::mat4 Entity::getModelMatrix()
{
	if (_transformReCalcRequired){

		glm::mat4 translationMatrix = glm::translate(glm::vec3(_pos.x, _pos.y, _pos.z));
		glm::mat4 scaleMatrix = glm::scale(_scale);

		_transform = translationMatrix * getRotationMatrix() * scaleMatrix;
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
