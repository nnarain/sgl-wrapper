
#pragma once

#ifndef SGLCOORDINATE_H
#define SGLCOORDINATE_H

#include "SGLExport.h"

namespace sgl
{
	SGLVOIDFUNC setWindowDimensions(float width, float height);
	SGLFLOATFUNC getWindowWidth();
	SGLFLOATFUNC getWindowHeight();

	namespace util
	{
		SGLVOIDFUNC pixelToNDC(float pixelX, float pixelY, float* ndcX, float* ndcY);
	};
};

#endif
