
#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Util/Camera.h"

namespace sgl
{
	SGLCLASS OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float viewportWidth, float viewportHeight, Vector2 x, Vector2 y, Vector2 z);

	protected:

	private:

		float _left, _right;
		float _top,  _bottom;
		float _near, _far;

		void calculateProjectionMatrix();
	};
}

#endif
