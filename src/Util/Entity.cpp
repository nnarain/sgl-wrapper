#include "SGL/Util/Entity.h"

#include <algorithm>

using namespace sgl;

Entity::Entity(void) :
	_position(0,0,0),
	_angle(0,0,0),
	_scale(1,1,1),
	_transformDirty(true),
	_normalDirty(true)
{
}

void Entity::translate(const Vector3& t)
{
	translate(t.x, t.y, t.z);
}

void Entity::translate(float x, float y, float z)
{
	_position.x += x;
	_position.y += y;
	_position.z += z;
	
	_transformDirty = true;
}

void Entity::setPosition(const Vector3& newPos)
{
	setPosition(newPos.x, newPos.y, newPos.z);
}

void Entity::setPosition(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;

	_transformDirty = true;
}

void Entity::rotate(const Vector3& r)
{
	rotate(r.x, r.y, r.z);
}

void Entity::rotate(float x, float y, float z)
{
	_angle.x += x;
	_angle.y += y;
	_angle.z += z;

	_transformDirty = true;
}

void Entity::scale(const Vector3& s)
{
	scale(s.x, s.y, s.z);
}

void Entity::scale(float x, float y, float z)
{
	_scale.x *= x;
	_scale.y *= y;
	_scale.z *= z;

	_transformDirty = true;
}

void Entity::scale(float t)
{
	scale(t, t, t);
}

Matrix4& Entity::getModelMatrix(void)
{
	if (_transformDirty)
	{
		_transform.toScale(_scale);
		_transform.rotate(_angle);
		_transform.translate(_position);

		_transformDirty = false;
	}

	return _transform;
}

Matrix3& Entity::getNormalMatrix(void)
{
	if (_normalDirty)
	{
		// the inverse transpose of the model matrix is the normal matrix
	}
}

Entity::~Entity(void)
{
}
