
#ifndef RECT_H
#define RECT_H

#include <SGL/Util/SGLExport.h>

#include "SGL/Math/Vector2.h"

namespace sgl
{
	SGLCLASS Rect
	{
	public:

		Vector2 bottomLeft;
		Vector2 topLeft;
		Vector2 topRight;
		Vector2 bottomRight;

	private:
	};
}

#endif
