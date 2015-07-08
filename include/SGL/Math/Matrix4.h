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
		void toScale(float t);

		void toRotation(const Vector3 &v, float angle);

		Matrix3 toNormalMatrix();

		/* Transforms */

		void translate(const Vector3& v);
		void translate(float, float, float);

		void scale(const Vector3& v);
		void scale(float);
		void scale(float, float, float);

		void rotate(const Vector3& v);
		void rotate(float, float, float);

		/* General Matrix */

		void toIdentity(void);
		
		void invert(void);
		
		void clear(void);

		float det(void);

		void transpose(void);

		/* Opengl Matrices */

		void lookAt(Vector3 eye, Vector3 center, Vector3 up);
		void perspective(float fov, float aspectRatio, float near, float far);

		/*  */
		Matrix3 toMatrix3(void) const;

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
		void set(const Matrix4& m);
		void set(float * m);
		
		const float * get(void) const;

	private:
		// matrix values
		float _mat[4 * 4];
	};
}

#endif