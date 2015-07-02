
#include "SGL/Type/Geometry.h"
#include "SGL/Util/SGLCoordinate.h"

SGLVOIDFUNC sgl::util::makeQuad(sgl::Rect& rect, float pixelX, float pixelY, float pixelW, float pixelH)
{
	float x1, y1, x2, y2;
	sgl::util::pixelToNDC(pixelX, pixelY, &x1, &y1);
	sgl::util::pixelToNDC(pixelX + pixelW, pixelY + pixelH, &x2, &y2);

	rect.bottomLeft.x = x1;
	rect.bottomLeft.y = y1;

	rect.topLeft.x = x1;
	rect.topLeft.y = y2;

	rect.topRight.x = x2;
	rect.topRight.y = y2;

	rect.bottomRight.x = x2;
	rect.bottomRight.y = y1;
}

