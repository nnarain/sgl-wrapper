
#include "SGL/Math/Matrix2.h"

#include <cassert>

using namespace sgl;

#define M00 0
#define M01 1

#define M10 2
#define M11 3

Matrix2::Matrix2()
{
}

float Matrix2::det(void)
{
	return (_mat[M00] * _mat[M11]) - (_mat[M10] * _mat[M01]);
}

float* Matrix2::operator[](unsigned int idx)
{
	assert(idx < 2 && "Matrix subscript out of range");
	return _mat + (idx * 3);
}

const float* Matrix2::operator[](unsigned int idx) const
{
	assert(idx < 2 && "Matrix subscript out of range");
	return _mat + (idx * 3);
}