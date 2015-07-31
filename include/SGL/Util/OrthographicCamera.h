
#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Util/Camera.h"
#include "SGL/Math/Vector2.h"

namespace sgl
{
	SGLCLASS OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float viewportWidth, float viewportHeight, Vector2f x, Vector2f y, Vector2f z);

	protected:

	private:

		float _left, _right;
		float _top,  _bottom;
		float _near, _far;

		void calculateProjectionMatrix();
	};
}

#endif
