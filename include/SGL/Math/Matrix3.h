
#ifndef MATRIX3_H
#define MATRIX3_H

#include "SGL/Util/SGLExport.h"

#include <SGL/Math/Vector3.h>

namespace sgl
{
	SGLCLASS Matrix3
	{
	public:
		Matrix3(void);
		Matrix3(float * m);

		void toCrossProduct(const Vector3&);

		void clear(void);
		void toIdentity(void);

		float det(void);

		void invert(void);
		void transpose(void);

		void set(float * m);

		/* Operators */
		Matrix3 operator*(const Matrix3&);
		Matrix3 operator+(const Matrix3&);

		Matrix3 operator*(float s);

		float* operator[](unsigned int idx);
		const float* operator[](unsigned int idx) const;

	private:
		float _mat[3 * 3];
	};
}

#endif

