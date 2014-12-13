
#pragma once

#ifndef INTERSECTOR_H
#define INTERSENCTOR_H

#include "SGLExport.h"

#include "Geometry.h"

namespace sgl
{
	SGLCLASS Intersector
	{
	public:
		static bool intersectRaySphere(Ray ray, BoundingSphere sphere);
		static bool intersectRayBox(Ray ray, BoundingBox bbox);
	};
}

#endif
