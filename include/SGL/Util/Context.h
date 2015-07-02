
#ifndef CONTEXT_H
#define CONTEXT_H

#include "SGL/Util/SGLExport.h"
#include "SGL/Math/Vector2.h"

#include <GL/glew.h>

namespace sgl
{
	SGLCLASS Context
	{
	public:

		enum class BufferBits
		{
			COLOR       = GL_COLOR_BUFFER_BIT,
			DEPTH       = GL_DEPTH_BUFFER_BIT,

			COLOR_DEPTH = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
		};

		static void clear(BufferBits bits);

		static void    setViewPortDimension(float width, float height);
		static Vector2 getViewPortDimensions(void);
		static float   getViewPortWidth(void);
		static float   getViewPortHeight(void);
		static float   getScreenAspectRatio(void);

		static Vector2 pixelToNDC(float x, float y);

	private:

		static Vector2 _viewPort;

	};
}

#endif
