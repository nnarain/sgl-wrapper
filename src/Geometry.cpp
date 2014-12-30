
#include "SGL/Geometry.h"
#include "SGL/SGLCoordinate.h"

SGLVOIDFUNC sgl::util::makeQuad(sgl::Quad& quad, float pixelX, float pixelY, float pixelW, float pixelH)
{
	float x1, y1, x2, y2;
	sgl::util::pixelToNDC(pixelX, pixelY, &x1, &y1);
	sgl::util::pixelToNDC(pixelX + pixelW, pixelY + pixelH, &x2, &y2);

	quad.bottomLeft.x = x1;
	quad.bottomLeft.y = y1;

	quad.topLeft.x = x1;
	quad.topLeft.y = y2;

	quad.topRight.x = x2;
	quad.topRight.y = y2;

	quad.bottomRight.x = x2;
	quad.bottomRight.y = y1;
}

