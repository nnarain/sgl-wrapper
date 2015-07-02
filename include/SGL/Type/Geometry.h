
#pragma once

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Math/Rect.h"
#include "SGL/Math/Vector2.h"
#include "SGL/Math/Vector3.h"

namespace sgl
{
	namespace util
	{
		SGLVOIDFUNC makeQuad(Rect& rect, float x, float y, float w, float h);
	};
};

#endif
