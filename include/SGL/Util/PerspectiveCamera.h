
#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Util/Camera.h"

#include "SGL/Math/Matrix4.h"
#include "SGL/Math/Vector4.h"

namespace sgl
{
	SGLCLASS PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float viewportWidth, float viewportHeight);

	private:
		//! field of view
		float _fov;


		void calculateProjectionMatrix(void);
	};
}

#endif
