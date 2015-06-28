
#ifndef CONTEXT_H
#define CONTEXT_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Math/Vector2.h"

namespace sgl
{
	SGLCLASS Context
	{
	public:

		static void    setViewPortDimension(float width, float height);
		static Vector2 getViewPortDimensions(void);
		static float   getViewPortWidth(void);
		static float   getViewPortHeight(void);
		static float   getScreenAspectRatio(void);

	private:

		static Vector2 _viewPort;

	};
}

#endif
