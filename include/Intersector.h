
#pragma once

#ifndef INTERSECTOR_H
#define INTERSENCTOR_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include "Ray.h"
#include "BoundingSphere.h"

namespace sgl
{
#ifdef _MSC_VER
	class DLLEXPORT Intersector
#else
	class Intersector
#endif
	{
		static bool raysphere(Ray ray, BoundingSphere sphere);
	};
}

#endif
