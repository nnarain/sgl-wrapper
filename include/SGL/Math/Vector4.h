
#ifndef VECTOR4_H
#define VECTOR4_H

#include <SGL/Util/SGLExport.h>

#include <SGL/Math/Vector3.h>

namespace sgl
{
	SGLCLASS Vector4
	{
	public:
		/* Vector Components */
		float x;
		float y;
		float z;
		float w;

		/* Constructors */
		Vector4();
		Vector4(const Vector3 &v, float w);
		Vector4(float x, float y, float z, float w);

		~Vector4();

		/*  */

		float length() const;
		Vector4& normalize();

		float dot(const Vector4 &v);
		Vector4& cross(const Vector4& v);

		/* Operators */
		Vector4 operator+(const Vector4& v);
		Vector4 operator-(const Vector4& v);
		Vector4 operator*(float s);
		Vector4 operator/(float s);

		Vector4& operator-();
		Vector4& operator+=(const Vector4& v);
		Vector4& operator-=(const Vector4& v);
		Vector4& operator*=(float s);
		Vector4& operator/=(float s);

		bool operator==(const Vector4 &v);
		bool operator!=(const Vector4 &v);
	};
}

#endif