
#ifndef VECTOR4_H
#define VECTOR4_H

#include <SGL/Util/SGLExport.h>

#include <SGL/Math/Vector3.h>

#include <cstdint>

namespace sgl
{
	template<typename T>
	SGLCLASS Vector4
	{
	public:
		/* Vector Components */
		T x;
		T y;
		T z;
		T w;

		/* Constructors */
		Vector4() : Vector4(0, 0, 0, 0)
		{
		}

		Vector4(const Vector3<T> &v, T w) : Vector4(v.x, v.y, v.z, w)
		{
		}

		Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
		{
		}

		~Vector4<T>()
		{
		}

		/*  */

		float length() const
		{
			return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
		}

		Vector4& normalize()
		{
			float magnitude = length();
			*this /= magnitude;

			return *this;
		}

		float dot(const Vector4 &v)
		{
			return ((this->x * v.x) + (this->y * v.y) + (this->z * v.z));
		}

		Vector4& cross(const Vector4& v)
		{
			float ax = this->x, ay = this->y, az = this->z;
			float bx = v.x, by = v.y, bz = v.z;

			this->x = (ay * bz) - (az * by);
			this->y = (az * bx) - (ax * bz);
			this->z = (ax * by) - (ay * bx);

			return *this;
		}

		/* Operators */
		Vector4 operator+(const Vector4& v)
		{
			return Vector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
		}

		Vector4 operator-(const Vector4& v)
		{
			return Vector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
		}

		Vector4 operator*(float s)
		{
			return Vector4(this->x * s, this->y * s, this->z * s, this->w / s);
		}

		Vector4 operator/(float s)
		{
			return Vector4(this->x / s, this->y / s, this->z / s, this->w / s);
		}

		Vector4& operator-()
		{
			this->x *= -1;
			this->y *= -1;
			this->z *= -1;

			return *this;
		}

		Vector4& operator+=(const Vector4& v)
		{
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;

			return *this;
		}

		Vector4& operator-=(const Vector4& v)
		{
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;

			return *this;
		}

		Vector4& operator*=(float s)
		{
			this->x *= s;
			this->y *= s;
			this->z *= s;

			return *this;
		}

		Vector4& operator/=(float s)
		{
			this->x /= s;
			this->y /= s;
			this->z /= s;

			return *this;
		}

		bool operator==(const Vector4 &v)
		{
			return this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w;
		}

		bool operator!=(const Vector4 &v)
		{
			return !((*this) == v);
		}
	};

	typedef Vector4<float       > Vector4f;
	typedef Vector4<double      > Vector4f64;
	
	typedef Vector4<int         > Vector4i;
	typedef Vector4<int64_t     > Vector4i64;
	typedef Vector4<int32_t     > Vector4i32;
	typedef Vector4<int16_t     > Vector4i16;
	typedef Vector4<int8_t      > Vector4i8;
	

	typedef Vector4<unsigned int> Vector4ui;
	typedef Vector4<uint64_t    > Vector4ui64;
	typedef Vector4<uint32_t    > Vector4ui32;
	typedef Vector4<uint16_t    > Vector4ui16;
	typedef Vector4<uint8_t     > Vector4ui8;

	typedef Vector4<bool        > Vector4b;
}

#endif