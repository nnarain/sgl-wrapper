
#ifndef VECTOR3_H
#define VECTOR3_H

#include <SGL/Util/SGLExport.h>

namespace sgl
{
	SGLCLASS Vector3
	{
	public:
		/* Vector Components */
		float x;
		float y;
		float z;

		/* Constructors */
		Vector3();
		Vector3(float x, float y, float z);

		~Vector3();

		/*  */

		float length() const;
		Vector3& normalize();

		float dot(const Vector3 &v);
		Vector3& cross(const Vector3& v);

		float proj(const Vector3& v);

		Vector3& set(const Vector3 & v);
		Vector3& set(float x, float y, float z);

		/* Operators */
		Vector3 operator+(const Vector3& v);
		Vector3 operator-(const Vector3& v);
		Vector3 operator*(float s);
		Vector3 operator/(float s);

		Vector3& operator-();
		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator*=(float s);
		Vector3& operator/=(float s);

		bool operator==(const Vector3& v);
		bool operator!=(const Vector3& v);
	};
}

#endif