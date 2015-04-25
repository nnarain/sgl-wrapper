
#include "SGL/Math/Vector4.h"

#include <cmath>

using namespace sgl;

/* Constructors */

Vector4::Vector4() : Vector4(0, 0, 0, 0)
{
}

Vector4::Vector4(const Vector3 &v, float w) : Vector4(v.x, v.y, v.z, w)
{
}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

/* Public Functions */

float Vector4::length() const
{
	return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

Vector4& Vector4::normalize()
{
	float magnitude = length();
	*this /= magnitude;

	return *this;
}

float Vector4::dot(const Vector4 &v)
{
	return ((this->x * v.x) + (this->y * v.y) + (this->z * v.z));
}

Vector4& Vector4::cross(const Vector4& v)
{
	float ax = this->x, ay = this->y, az = this->z;
	float bx = v.x, by = v.y, bz = v.z;

	this->x = (ay * bz) - (az * by);
	this->y = (az * bx) - (ax * bz);
	this->z = (ax * by) - (ay * bx);

	return *this;
}

Vector4 Vector4::operator+(const Vector4& v)
{
	return Vector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
}

Vector4 Vector4::operator-(const Vector4& v)
{
	return Vector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
}

Vector4 Vector4::operator*(float s)
{
	return Vector4(this->x * s, this->y * s, this->z * s, this->w / s);
}

Vector4 Vector4::operator/(float s)
{
	return Vector4(this->x / s, this->y / s, this->z / s, this->w / s);
}

Vector4& Vector4::operator-()
{
	this->x *= -1;
	this->y *= -1;
	this->z *= -1;

	return *this;
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;

	return *this;
}

Vector4& Vector4::operator-=(const Vector4& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;

	return *this;
}

Vector4& Vector4::operator*=(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;

	return *this;
}

Vector4& Vector4::operator/=(float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;

	return *this;
}

Vector4::~Vector4()
{
}