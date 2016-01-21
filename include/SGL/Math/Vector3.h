
#ifndef VECTOR3_H
#define VECTOR3_H

#include <SGL/Util/SGLExport.h>

#include <cstdint>

namespace sgl
{
	template<typename T>
	SGLCLASS Vector3
	{
	public:
		/* Vector Components */
		T x;
		T y;
		T z;

		/* Constructors */
		Vector3<T>() : Vector3<T>(0, 0, 0)
		{
		}

		Vector3<T>(T x, T y, T z) : x(x), y(y), z(z)
		{
		}

		~Vector3<T>()
		{
		}

		/*  */

		float length() const
		{
			return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
		}

		Vector3<T>& normalize()
		{
			float magnitude = length();
			*this /= magnitude;

			return *this;
		}

		float dot(const Vector3<T> &v)
		{
			return ((this->x * v.x) + (this->y * v.y) + (this->z * v.z));
		}

		Vector3<T>& cross(const Vector3<T>& v)
		{
			float ax = this->x, ay = this->y, az = this->z;
			float bx = v.x, by = v.y, bz = v.z;

			this->x = (ay * bz) - (az * by);
			this->y = (az * bx) - (ax * bz);
			this->z = (ax * by) - (ay * bx);

			return *this;
		}

		float proj(const Vector3<T>& v)
		{
			return abs(this->dot(w)) / this->length();
		}

		Vector3<T>& set(const Vector3<T> & v)
		{
			return set(v.x, v.y, v.z);
		}

		Vector3<T>& set(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;

			return *this;
		}

		/* Operators */
		Vector3<T> operator+(const Vector3<T>& v)
		{
			return Vector3<T>(this->x + v.x, this->y + v.y, this->z + v.z);
		}

		Vector3<T> operator-(const Vector3<T>& v)
		{
			return Vector3<T>(this->x - v.x, this->y - v.y, this->z - v.z);
		}

		Vector3<T> operator*(float s)
		{
			return Vector3<T>(this->x * s, this->y * s, this->z * s);
		}

		Vector3<T> operator/(float s)
		{
			return Vector3<T>(this->x / s, this->y / s, this->z / s);
		}

		Vector3<T> operator-()
		{
			return Vector3(this->x * -1, this->y * -1, this->z * -1);
		}

		Vector3<T>& operator+=(const Vector3<T>& v)
		{
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;

			return *this;
		}

		Vector3<T>& operator-=(const Vector3<T>& v)
		{
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;

			return *this;
		}

		Vector3<T>& operator*=(float s)
		{
			this->x *= s;
			this->y *= s;
			this->z *= s;

			return *this;
		}

		Vector3<T>& operator/=(float s)
		{
			this->x /= s;
			this->y /= s;
			this->z /= s;

			return *this;
		}

		bool operator==(const Vector3<T>& v)
		{
			return this->x == v.x && this->y == v.y && this->z == v.z;
		}

		bool operator!=(const Vector3<T>& v)
		{
			return !((*this) == v);
		}
	};

	typedef Vector3<float       > Vector3f  ;
	typedef Vector3<double      > Vector3f64;

	typedef Vector3<int         > Vector3i  ;
	typedef Vector3<int64_t     > Vector3i64;
	typedef Vector3<int32_t     > Vector3i32;
	typedef Vector3<int16_t     > Vector3i16;
	typedef Vector3<int8_t      > Vector3i8;

	typedef Vector3<unsigned int> Vector3ui;
	typedef Vector3<uint64_t    > Vector3ui64;
	typedef Vector3<uint32_t    > Vector3ui32;
	typedef Vector3<uint16_t    > Vector3ui16;
	typedef Vector3<uint8_t     > Vector3ui8 ;

	typedef Vector3<bool        > Vector3b  ;

}

#endif