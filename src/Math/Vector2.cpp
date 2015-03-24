
#include "SGL/Math/Vector2.h"

using namespace sgl;

Vector2::Vector2() : Vector2(0, 0)
{
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
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