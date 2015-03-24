
#include "SGL/Math/Vector2.h"

#include <cmath>

using namespace sgl;

Vector2::Vector2() : Vector2(0, 0)
{
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

float Vector2::length() const
{
	return std::sqrt( (this->x * this->x) + (this->y * this->y) );
}

Vector2& Vector2::normalize()
{
	float magnitude = length();
	*this /= magnitude;

	return *this;
}

float Vector2::dot(const Vector2 &v)
{
	return ( (this->x * v.x) + (this->y * v.y) );
}

float Vector2::cross(const Vector2& v)
{
	return (this->x * v.y - this->y * v.x);
}

Vector2 Vector2::operator+(const Vector2& v)
{
	return Vector2(this->x + v.x, this->y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v)
{
	return Vector2(this->x - v.x, this->y - v.y);
}

Vector2 Vector2::operator*(float s)
{
	return Vector2(this->x * s, this->y * s);
}

Vector2 Vector2::operator/(float s)
{
	return Vector2(this->x / s, this->y / s);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	this->x += v.x;
	this->y += v.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	this->x -= v.x;
	this->y -= v.y;

	return *this;
}

Vector2& Vector2::operator*=(float s)
{
	this->x *= s;
	this->y *= s;

	return *this;
}

Vector2& Vector2::operator/=(float s)
{
	this->x /= s;
	this->y /= s;

	return *this;
}

Vector2::~Vector2()
{
}