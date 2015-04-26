
#include "SGL/Math/Matrix4.h"

#include <cassert>

using namespace sgl;

#define M00 0
#define M01 1
#define M02 2
#define M03 3

#define M10 4
#define M11 5
#define M12 6
#define M13 7

#define M20 8
#define M21 9
#define M22 10
#define M23 11

#define M30 12
#define M31 13
#define M32 14
#define M33 15

#define MTX M30
#define MTY M31
#define MTZ M32

#define MSX M00
#define MSY M11
#define MSZ M22

#define PI              3.14159f
#define DEG_TO_RAD(deg) ((deg) * (PI/180.0f))

Matrix4::Matrix4()
{
	// init the matrix to zero
	clear();
}

Matrix4::Matrix4(float *m)
{
	set(m);
}

void Matrix4::toTranslation(const Vector3 &v)
{
	toTranslation(v.x, v.y, v.z);
}

void Matrix4::toTranslation(float x, float y, float z)
{
	// reset the matrix
	clear();

	_mat[M00] = 1;
	_mat[M11] = 1;
	_mat[M22] = 1;
	_mat[M33] = 1;

	_mat[MTX] = x;
	_mat[MTY] = y;
	_mat[MTZ] = z;
}

void Matrix4::toScale(const Vector3 &v)
{
	toScale(v.x, v.y, v.z);
}

void Matrix4::toScale(float x, float y, float z)
{
	clear();

	_mat[MSX] = x;
	_mat[MSY] = y;
	_mat[MSZ] = z;
	_mat[M33] = 1;
}

/**
	Rodrigues Rotation Matrix

	Formula: 
	R = I + sin(x) * K + (1 - cos(x)) * K^2

	Identity Matrix

	    [ 1 0 0 ]
	I = [ 0 1 0 ]
		[ 0 0 1 ]

	Cross Product Matrix

		[   0 -k3   k2 ]
	K =	[  k3   0  -k1 ]
		[ -k2  k1    0 ]
*/
void Matrix4::toRotation(const Vector3 &v, float a)
{
	// copy and normalize the rotation vector
	Vector3 axis(v);
	axis.normalize();

	// convert parameter to radians
	a = DEG_TO_RAD(a);

	// create required matrices

	// identity matrix
	Matrix3 I;
	I.toIdentity();

	// unit vector cross product matrix
	Matrix3 K;
	K.toCrossProduct(axis);

	// resultant matrix
	Matrix3 R;

	// R = I + sin(x) * K + (1 - cos(x)) * K^2
	R = I + (K * sin(a)) + ((K * K) * (1.0f - cos(a)));

	set(R);

	_mat[M33] = 1;
}

/* Transforms */

void Matrix4::translate(const Vector3& v)
{
	translate(v.x, v.y, v.z);
}

void Matrix4::translate(float x, float y, float z)
{
	Matrix4 T;
	T.toTranslation(x, y, z);

	Matrix4 R;

	R = *this * T;

	set(R);
}

void Matrix4::rotate(const Vector3& v)
{
	rotate(v.x, v.y, v.z);
}

void Matrix4::rotate(float x, float y, float z)
{
	Matrix4 Rx, Ry, Rz;

	Rx.toRotation(Vector3(1, 0, 0), x);
	Ry.toRotation(Vector3(0, 1, 0), y);
	Rz.toRotation(Vector3(0, 0, 1), z);

	Matrix4 R = (*this) * Rx * Ry * Rz;

	set(R);
}

void Matrix4::toIdentity()
{
	clear();

	_mat[M00] = 1;
	_mat[M11] = 1;
	_mat[M22] = 1;
	_mat[M33] = 1;
}

void Matrix4::clear(void)
{
	int i;
	for (i = 0; i < 16; ++i)
	{
		_mat[i] = 0;
	}
}

/* Operators */

Vector4 Matrix4::operator*(const Vector4 &v)
{
	float x;
	float y;
	float z;
	float w;

	x = (_mat[M00] * v.x) + (_mat[M10] * v.y) + (_mat[M20] * v.z) + (_mat[M30] * v.w);
	y = (_mat[M01] * v.x) + (_mat[M11] * v.y) + (_mat[M21] * v.z) + (_mat[M31] * v.w);
	z = (_mat[M02] * v.x) + (_mat[M12] * v.y) + (_mat[M22] * v.z) + (_mat[M32] * v.w);
	w = (_mat[M03] * v.x) + (_mat[M13] * v.y) + (_mat[M23] * v.z) + (_mat[M33] * v.w);

	return Vector4(x, y, z, w);
}

Matrix4 Matrix4::operator*(const Matrix4 &m)
{
	float newMat[4 * 4];

	newMat[M00] = (_mat[M00] * m[0][0]) + (_mat[M10] * m[0][1]) + (_mat[M20] * m[0][2]) + (_mat[M30] * m[0][3]);
	newMat[M10] = (_mat[M00] * m[1][0]) + (_mat[M10] * m[1][1]) + (_mat[M20] * m[1][2]) + (_mat[M30] * m[1][3]);
	newMat[M20] = (_mat[M00] * m[2][0]) + (_mat[M10] * m[2][1]) + (_mat[M20] * m[2][2]) + (_mat[M30] * m[2][3]);
	newMat[M30] = (_mat[M00] * m[3][0]) + (_mat[M10] * m[3][1]) + (_mat[M20] * m[3][2]) + (_mat[M30] * m[3][3]);

	newMat[M01] = (_mat[M01] * m[0][0]) + (_mat[M11] * m[0][1]) + (_mat[M21] * m[0][2]) + (_mat[M31] * m[0][3]);
	newMat[M11] = (_mat[M01] * m[1][0]) + (_mat[M11] * m[1][1]) + (_mat[M21] * m[1][2]) + (_mat[M31] * m[1][3]);
	newMat[M21] = (_mat[M01] * m[2][0]) + (_mat[M11] * m[2][1]) + (_mat[M21] * m[2][2]) + (_mat[M31] * m[2][3]);
	newMat[M31] = (_mat[M01] * m[3][0]) + (_mat[M11] * m[3][1]) + (_mat[M21] * m[3][2]) + (_mat[M31] * m[3][3]);

	newMat[M02] = (_mat[M02] * m[0][0]) + (_mat[M12] * m[0][1]) + (_mat[M22] * m[0][2]) + (_mat[M32] * m[0][3]);
	newMat[M12] = (_mat[M02] * m[1][0]) + (_mat[M12] * m[1][1]) + (_mat[M22] * m[1][2]) + (_mat[M32] * m[1][3]);
	newMat[M22] = (_mat[M02] * m[2][0]) + (_mat[M12] * m[2][1]) + (_mat[M22] * m[2][2]) + (_mat[M32] * m[2][3]);
	newMat[M32] = (_mat[M02] * m[3][0]) + (_mat[M12] * m[3][1]) + (_mat[M22] * m[3][2]) + (_mat[M32] * m[3][3]);

	newMat[M03] = (_mat[M03] * m[0][0]) + (_mat[M13] * m[0][1]) + (_mat[M23] * m[0][2]) + (_mat[M33] * m[0][3]);
	newMat[M13] = (_mat[M03] * m[1][0]) + (_mat[M13] * m[1][1]) + (_mat[M23] * m[1][2]) + (_mat[M33] * m[1][3]);
	newMat[M23] = (_mat[M03] * m[2][0]) + (_mat[M13] * m[2][1]) + (_mat[M23] * m[2][2]) + (_mat[M33] * m[2][3]);
	newMat[M33] = (_mat[M03] * m[3][0]) + (_mat[M13] * m[3][1]) + (_mat[M23] * m[3][2]) + (_mat[M33] * m[3][3]);

	return Matrix4(newMat);
}

Matrix4& Matrix4::operator*=(float s)
{
	int i;
	for (i = 0; i < 16; i++)
	{
		_mat[i] *= s;
	}
	return *this;
}

float* Matrix4::operator[](unsigned int idx)
{
	assert(idx < 4 && "Matrix subscript out of range");
	return _mat + (idx * 4);
}

const float* Matrix4::operator[](unsigned int idx) const
{
	assert(idx < 4 && "Matrix subscript out of range");
	return _mat + (idx * 4);
}

void Matrix4::set(const Matrix3& m)
{
	int i, j;

	clear();

	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			(*this)[i][j] = m[i][j];
		}
	}
}

void Matrix4::set(const Matrix4& m)
{
	const float *ptr = m.get();
	int i;
	for (i = 0; i < 16; ++i)
	{
		_mat[i] = ptr[i];
	}
}

void Matrix4::set(float * m)
{
	int i;
	for (i = 0; i < 16; ++i)
	{
		_mat[i] = m[i];
	}
}

const float * Matrix4::get() const
{
	return _mat;
}

std::ostream& operator<<(std::ostream& os, const Matrix4& m)
{
	int i, j;
	for (i = 0; i < 4; ++i)
	{
		os << "[ ";

		for (j = 0; j < 4; ++j)
		{
			os << m[i][j] << " ";
		}

		os << "]\n";
	}

	return os;
}