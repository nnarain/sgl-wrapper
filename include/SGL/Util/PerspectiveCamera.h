
#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Util/Camera.h"

#include "SGL/Math/Vector4.h"
#include "SGL/Math/Matrix4.h"
#include "SGL/Math/Frustum.h"

namespace sgl
{
	SGLCLASS PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float viewportWidth, float viewportHeight);
		
		/**
			update the perspective camera
		*/
		void update(void);


		/**
			Get the frustum
		*/
		Frustum& getFrustum(void);

		/**
			Get the Camera field of view
		*/
		float getFieldOfView(void) const;

	private:
		//! field of view
		float _fov;

		Frustum _frustum;

		void calculateProjectionMatrix(void);
	};
}

#endif
