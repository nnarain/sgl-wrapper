
#ifndef VECTOR2_H
#define VECTOR2_H

#include <SGL/Util/SGLExport.h>

#include <cstdint>

namespace sgl
{
	template <typename T>
	SGLCLASS Vector2
	{
	public:
		/* Vector Components */

		T x;
		T y;


		/* Constructors */
		Vector2<T>() : Vector2<T>(0, 0)
		{
		}

		Vector2<T>(T x, T y) : x(x), y(y)
		{
		}

		~Vector2<T>()
		{
		}

		/*  */

		float length() const
		{
			return std::sqrt((this->x * this->x) + (this->y * this->y));
		}

		Vector2<T>& normalize()
		{
			float magnitude = length();
			*this /= magnitude;

			return *this;
		}

		float dot(const Vector2<T> &v)
		{
			return ((this->x * v.x) + (this->y * v.y));
		}

		float cross(const Vector2<T>& v)
		{
			return (this->x * v.y - this->y * v.x);
		}

		/* Operators */
		Vector2<T> operator+(const Vector2& v)
		{
			return Vector2<T>(this->x + v.x, this->y + v.y);
		}

		Vector2<T> operator-(const Vector2& v)
		{
			return Vector2<T>(this->x - v.x, this->y - v.y);
		}

		Vector2<T> operator*(float s)
		{
			return Vector2<T>(this->x * s, this->y * s);
		}

		Vector2<T> operator/(float s)
		{
			return Vector2<T>(this->x / s, this->y / s);
		}

		Vector2<T>& operator-()
		{
			this->x *= -1;
			this->y *= -1;

			return *this;
		}

		Vector2<T>& operator+=(const Vector2<T>& v)
		{
			this->x += v.x;
			this->y += v.y;

			return *this;
		}

		Vector2<T>& operator-=(const Vector2<T>& v)
		{
			this->x -= v.x;
			this->y -= v.y;

			return *this;
		}

		Vector2<T>& operator*=(float s)
		{
			this->x *= s;
			this->y *= s;

			return *this;
		}

		Vector2<T>& operator/=(float s)
		{
			this->x /= s;
			this->y /= s;

			return *this;
		}

		bool operator==(const Vector2<T> &v)
		{
			return this->x == v.x && this->y == v.y;
		}

		bool operator!=(const Vector2<T> &v)
		{
			return !((*this) == v);
		}
	};

	typedef Vector2<float       > Vector2f;
	typedef Vector2<double      > Vector2f64;

	typedef Vector2<int         > Vector2i;
	typedef Vector2<int64_t     > Vector2i64;
	typedef Vector2<int32_t     > Vector2i32;
	typedef Vector2<int16_t     > Vector2i16;
	typedef Vector2<int8_t      > Vector2i8;

	typedef Vector2<unsigned int> Vector2ui;
	typedef Vector2<uint64_t    > Vector2ui64;
	typedef Vector2<uint32_t    > Vector2ui32;
	typedef Vector2<uint16_t    > Vector2ui16;
	typedef Vector2<uint8_t     > Vector2ui8;

	typedef Vector2<bool        > Vector2b;
}

#endif
