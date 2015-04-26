
#include <SGL/Math/Matrix3.h>
#include <SGL/Math/Matrix2.h>

#include <cassert>

using namespace sgl;

#define M00 0
#define M01 1
#define M02 2

#define M10 3
#define M11 4
#define M12 5

#define M20 6
#define M21 7
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

float Matrix3::det(void)
{
	Matrix2 mats[3];

	// create 2x2 matrices for determinant
	int i;
	int col, row;
	int mCol, mRow;

	for (i = 0; i < 3; ++i)
	{
		// the current matrix to populate
		Matrix2& m = mats[i];

		mCol = 0;

		for (col = 0; col < 3; ++col)
		{
			mRow = 0;

			// if is the same column
			if (col == i) continue;

			for (row = 0; row < 3; ++row)
			{
				// if in the same row
				if (row == 0) continue;

				m[mCol][mRow] = (*this)[col][row];

				mRow++;
			}

			mCol++;
		}
	}

	// calculate the 3x3 matrix determinant
	return ((*this)[0][0] * mats[0].det()) - ((*this)[1][0] * mats[1].det()) + ((*this)[2][0] * mats[2].det());
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