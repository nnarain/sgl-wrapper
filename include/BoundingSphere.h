
#pragma once

#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include "Entity.h"
#include <glm/vec3.hpp>

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

namespace sgl{

#ifdef _MSC_VER
	class DLLEXPORT BoundingSphere
#else
	class BoundingSphere
#endif
		: public Entity
	{
	public:
		BoundingSphere(float r, float x, float y, float z);
		BoundingSphere(float r, glm::vec3 pos);
		~BoundingSphere();

		float radius() const;

		static BoundingSphere create(glm::vec3* vertices, int size);

	private:
		float _radius;

		/* Sort functions */
		static int compare(const void* a, const void* b);
	};

};

#endif
