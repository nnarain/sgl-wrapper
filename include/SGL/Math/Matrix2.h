
#ifndef MATRIX2_H
#define MATRIX2_H

#include <SGL/Util/SGLExport.h>

namespace sgl
{
	SGLCLASS Matrix2
	{
	public:
		Matrix2();

		float det(void);

		float* operator[](unsigned int idx);
		const float* operator[](unsigned int idx) const;

	private:
		float _mat[2 * 2];
	};
}

#endif
