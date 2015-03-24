
#ifndef VECTOR2_H
#define VECTOR2_H

#include <SGL/Util/SGLExport.h>

namespace sgl
{
	SGLCLASS Vector2
	{
	public:
		/* Vector Components */
		float x;
		float y;

		/* Constructors */
		Vector2();
		Vector2(float x, float y);

		~Vector2();

		/*  */

		float length() const;
		Vector2& normalize();

		float dot(const Vector2 &v);
		float cross(const Vector2& v);

		/* Operators */
		Vector2 operator+(const Vector2& v);
		Vector2 operator-(const Vector2& v);
		Vector2 operator*(float s);
		Vector2 operator/(float s);

		Vector2& operator+=(const Vector2& v);
		Vector2& operator-=(const Vector2& v);
		Vector2& operator*=(float s);
		Vector2& operator/=(float s);
	};
}

#endif
