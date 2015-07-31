
#include <SGL/Math/Matrix3.h>

#include <cassert>
#include <algorithm>

using namespace sgl;

/* Matrix Position Names */

#define M00 0
#define M01 1
#define M02 2

#define M10 3
#define M11 4
#define M12 5

#define M20 6
#define M21 7
#define M22 8

/*
	Alternate Names

	| a b c |
	| d e f |
	| g h i |
*/

#define MA M00
#define MB M10
#define MC M20

#define MD M01
#define ME M11
#define MF M21

#define MG M02
#define MH M12
#define MI M22

Matrix3::Matrix3(void)
{
	clear();
}

Matrix3::Matrix3(float * m)
{
	set(m);
}

void Matrix3::toCrossProduct(const Vector3f& k)
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

float Matrix3::det(void)
{
	float det;

	det =
		  _mat[MA] * (_mat[ME] * _mat[MI] - _mat[MF] * _mat[MH])
		- _mat[MB] * (_mat[MD] * _mat[MI] - _mat[MF] * _mat[MG])
		+ _mat[MC] * (_mat[MD] * _mat[MH] - _mat[ME] * _mat[MG]);

	return det;
}

void Matrix3::invert(void)
{
	float newMat[3 * 3];
	float detM;
	float invDet;

	detM = det();

	assert(detM != 0 && "Determinant cannot be zero");

	invDet = 1.0f / detM;

	newMat[MA] = (_mat[ME] * _mat[MI] - _mat[MF] * _mat[MH]) * invDet; //
	newMat[MB] = (_mat[MC] * _mat[MH] - _mat[MB] * _mat[MI]) * invDet; //
	newMat[MC] = (_mat[MB] * _mat[MF] - _mat[ME] * _mat[MC]) * invDet; //
	newMat[MD] = (_mat[MF] * _mat[MG] - _mat[MD] * _mat[MI]) * invDet; //
	newMat[ME] = (_mat[MA] * _mat[MI] - _mat[MC] * _mat[MG]) * invDet; //
	newMat[MF] = (_mat[MC] * _mat[MD] - _mat[MA] * _mat[MF]) * invDet; //
	newMat[MG] = (_mat[MD] * _mat[MH] - _mat[ME] * _mat[MG]) * invDet; //
	newMat[MH] = (_mat[MB] * _mat[MG] - _mat[MA] * _mat[MH]) * invDet; //
	newMat[MI] = (_mat[MA] * _mat[ME] - _mat[MB] * _mat[MD]) * invDet; //

	set(newMat);
}

void Matrix3::transpose(void)
{
	using std::swap;

	Matrix3 m(*this);

	int i, j;

	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			(*this)[j][i] = m[i][j];
		}
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

	newMat[M00] = (_mat[M00] * m[0][0]) + (_mat[M10] * m[0][1]) + (_mat[M20] * m[0][2]);
	newMat[M10] = (_mat[M00] * m[1][0]) + (_mat[M10] * m[1][1]) + (_mat[M20] * m[1][2]);
	newMat[M20] = (_mat[M00] * m[2][0]) + (_mat[M10] * m[2][1]) + (_mat[M20] * m[2][2]);

	newMat[M01] = (_mat[M01] * m[0][0]) + (_mat[M11] * m[0][1]) + (_mat[M21] * m[0][2]);
	newMat[M11] = (_mat[M01] * m[1][0]) + (_mat[M11] * m[1][1]) + (_mat[M21] * m[1][2]);
	newMat[M21] = (_mat[M01] * m[2][0]) + (_mat[M11] * m[2][1]) + (_mat[M21] * m[2][2]);

	newMat[M02] = (_mat[M02] * m[0][0]) + (_mat[M12] * m[0][1]) + (_mat[M22] * m[0][2]);
	newMat[M12] = (_mat[M02] * m[1][0]) + (_mat[M12] * m[1][1]) + (_mat[M22] * m[1][2]);
	newMat[M22] = (_mat[M02] * m[2][0]) + (_mat[M12] * m[2][1]) + (_mat[M22] * m[2][2]);

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