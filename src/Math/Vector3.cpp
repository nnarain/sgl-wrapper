
#include "SGL/Math/Vector3.h"

#include <cmath>

using namespace sgl;

Vector3::Vector3() : Vector3(0, 0, 0)
{
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

float Vector3::length() const
{
	return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

Vector3& Vector3::normalize()
{
	float magnitude = length();
	*this /= magnitude;

	return *this;
}

float Vector3::dot(const Vector3 &v)
{
	return ((this->x * v.x) + (this->y * v.y) + (this->z * v.z));
}

Vector3& Vector3::cross(const Vector3& v)
{
	float ax = this->x, ay = this->y, az = this->z;
	float bx = v.x, by = v.y, bz = v.z;

	this->x = (ay * bz) - (az * by);
	this->y = (az * bx) - (ax * bz);
	this->z = (ax * by) - (ay * bx);

	return *this;
}

float Vector3::proj(const Vector3& w)
{
	return abs(this->dot(w)) / this->length();
}

Vector3& Vector3::set(const Vector3 & v)
{
	return set(v.x, v.y, v.z);
}

Vector3& Vector3::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	return *this;
}

/* Operators */

Vector3 Vector3::operator+(const Vector3& v)
{
	return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v)
{
	return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector3 Vector3::operator*(float s)
{
	return Vector3(this->x * s, this->y * s, this->z * s);
}

Vector3 Vector3::operator/(float s)
{
	return Vector3(this->x / s, this->y / s, this->z / s);
}

Vector3& Vector3::operator-()
{
	this->x *= -1;
	this->y *= -1;
	this->z *= -1;

	return *this;
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;

	return *this;
}

Vector3& Vector3::operator*=(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;

	return *this;
}

Vector3& Vector3::operator/=(float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;

	return *this;
}

bool Vector3::operator==(const Vector3& v)
{
	return this->x == v.x && this->y == v.y && this->z == v.z;
}

bool Vector3::operator!=(const Vector3& v)
{
	return !((*this) == v);
}

Vector3::~Vector3()
{
}