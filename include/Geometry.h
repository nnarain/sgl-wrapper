
#pragma once

#ifndef GEOMETRY_H
#define GEOMETRY_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <glm/vec3.hpp>

namespace sgl
{
	//! Ray
	struct Ray
	{
		glm::vec3 origin;
		glm::vec3 direction;
	};

#ifdef _MSC_VER
	class DLLEXPORT BoundingBox
#else
	class BoundingBox
#endif
	{
	public:
		BoundingBox();
		BoundingBox(glm::vec3 min, glm::vec3 max);

		~BoundingBox(void);

		glm::vec3 min() const;
		glm::vec3 max() const;

		static BoundingBox create(glm::vec3* vertices, int size);

	private:
		glm::vec3 _min;
		glm::vec3 _max;

		static int compareX(const void* a, const void* b);
		static int compareY(const void* a, const void* b);
		static int compareZ(const void* a, const void* b);
	};

	//! Sphere
#ifdef _MSC_VER
	class DLLEXPORT BoundingSphere
#else
	class BoundingSphere
#endif
	{
	public:
		BoundingSphere(float r, float x, float y, float z);
		BoundingSphere(float r, glm::vec3 pos);
		~BoundingSphere();

		float radius;
		glm::vec3 position;

		static BoundingSphere create(glm::vec3* vertices, int size);

	private:

		/* Sort functions */
		static int compare(const void* a, const void* b);
	};
};

#endif
