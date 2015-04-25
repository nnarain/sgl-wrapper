
#include <SGL/Math/Matrix3.h>

#include <cassert>

using namespace sgl;

#define M00 0
#define M01 3
#define M02 6

#define M10 1
#define M11 4
#define M12 7

#define M20 2
#define M21 5
#define M22 8


Matrix3::Matrix3(void)
{
}

Matrix3::Matrix3(float * m)
{
	set(m);
}

void Matrix3::toCrossProduct(const Vector3& k)
{
	_mat[M00] = 0;    _mat[M10] = -k.z; _mat[M20] = k.y;
	_mat[M01] = k.z;  _mat[M11] = 0;    _mat[M21] = -k.x;
	_mat[M02] = -k.y; _mat[M12] = k.x;  _mat[M22] = 0;
}

void Matrix3::toIdentity(void)
{
	clear();

	_mat[M00] = 1;
	_mat[M11] = 1;
	_mat[M22] = 1;
}

void Matrix3::clear(void)
{
	int i;
	for (i = 0; i < 9; ++i)
	{
		_mat[i] = 0;
	}
}

void Matrix3::set(float * m)
{
	int i;
	for (i = 0; i < 9; ++i)
	{
		_mat[i] = m[i];
	}
}

/* Operators */

Matrix3 Matrix3::operator*(const Matrix3 &m)
{
	float newMat[3 * 3];

	newMat[M00] = (_mat[M00] * m[0][0]) + (_mat[M10] * m[1][0]) + (_mat[M20] * m[2][0]);
	newMat[M10] = (_mat[M00] * m[0][1]) + (_mat[M10] * m[1][1]) + (_mat[M20] * m[2][1]);
	newMat[M20] = (_mat[M00] * m[0][2]) + (_mat[M10] * m[1][2]) + (_mat[M20] * m[2][2]);

	newMat[M01] = (_mat[M01] * m[0][0]) + (_mat[M11] * m[1][0]) + (_mat[M21] * m[2][0]);
	newMat[M11] = (_mat[M01] * m[0][1]) + (_mat[M11] * m[1][1]) + (_mat[M21] * m[2][1]);
	newMat[M21] = (_mat[M01] * m[0][2]) + (_mat[M11] * m[1][2]) + (_mat[M21] * m[2][2]);

	newMat[M02] = (_mat[M02] * m[0][0]) + (_mat[M12] * m[1][0]) + (_mat[M22] * m[2][0]);
	newMat[M12] = (_mat[M02] * m[0][1]) + (_mat[M12] * m[1][1]) + (_mat[M22] * m[2][1]);
	newMat[M22] = (_mat[M02] * m[0][2]) + (_mat[M12] * m[1][2]) + (_mat[M22] * m[2][2]);

	return Matrix3(newMat);
}

Matrix3 Matrix3::operator*(float s)
{
	float newMat[9];
	int i;

	for (i = 0; i < 9; ++i)
	{
		newMat[i] = _mat[i] * s;
	}

	return Matrix3(newMat);
}

Matrix3 Matrix3::operator+(const Matrix3& m)
{
	Matrix3 R;

	int i, j;
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			R[i][j] = (*this)[i][j] + m[i][j];
		}
	}

	return R;
}

float* Matrix3::operator[](unsigned int idx)
{
	assert(idx < 3 && "Matrix subscript out of range");
	return _mat + (idx * 3);
}

const float* Matrix3::operator[](unsigned int idx) const
{
	assert(idx < 3 && "Matrix subscript out of range");
	return _mat + (idx * 3);
}