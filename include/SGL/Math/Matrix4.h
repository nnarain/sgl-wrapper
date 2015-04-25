#ifndef MATRIX4_H
#define MATRIX4_H

#include <SGL/Util/SGLExport.h>

#include <SGL/Math/Matrix3.h>

#include <SGL/Math/Vector3.h>
#include <SGL/Math/Vector4.h>

#include <iostream>

namespace sgl
{
	SGLCLASS Matrix4
	{
	public:
		Matrix4(void);
		Matrix4(float *m);

		/* Special Matrices */

		void toTranslation(const Vector3 &v);
		void toTranslation(float x, float y, float z);

		void toScale(const Vector3 &v);
		void toScale(float x, float y, float z);

		void toRotation(const Vector3 &v, float angle);

		/* General Matrix */

		void toIdentity(void);
		void clear(void);

		/* Operators */

		Vector4 operator*(const Vector4 &v);
		Matrix4 operator*(const Matrix4 &m);

		Matrix4 &operator*=(float s);

		float* operator[](unsigned int idx);
		const float* operator[](unsigned int idx) const;

		// stream
		friend std::ostream& operator<<(std::ostream&, const Matrix4&);

		/* Getters and Setters */

		void set(const Matrix3& m);
		void set(float * m);
		
		const float * get(void) const;

	private:
		float _mat[4 * 4];
	};
}

#endif