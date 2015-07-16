
#ifndef RECT_H
#define RECT_H

#include <SGL/Util/SGLExport.h>

#include "SGL/Math/Vector2.h"

namespace sgl
{
	SGLCLASS Rect
	{
	public:

		Rect() : Rect(0,0,0,0)
		{
		}

		Rect(float x, float y, float w, float h) : x(x), y(y), width(w), height(h)
		{
		}

		float x;
		float y;
		float width;
		float height;

	private:
	};
}

#endif
