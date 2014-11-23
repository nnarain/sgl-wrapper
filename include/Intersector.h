
#pragma once

#ifndef INTERSECTOR_H
#define INTERSENCTOR_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include "Geometry.h"

namespace sgl
{
#ifdef _MSC_VER
	class DLLEXPORT Intersector
#else
	class Intersector
#endif
	{
	public:
		static bool raysphere(Ray ray, BoundingSphere sphere);
	};
}

#endif
