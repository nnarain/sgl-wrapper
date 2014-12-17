
#pragma once

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "SGLExport.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace sgl
{
	//! Ray
	struct Ray
	{
		glm::vec3 origin;
		glm::vec3 direction;
	};

	SGLCLASS BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox(glm::vec3 min, glm::vec3 max);

		~BoundingBox(void);

		glm::vec3 min() const;
		glm::vec3 max() const;
		glm::vec3 center() const;

		void transform(glm::mat4 transform);

		static BoundingBox create(glm::vec3* vertices, int size);

	private:
		glm::vec3 _min;
		glm::vec3 _max;

		static int compareX(const void* a, const void* b);
		static int compareY(const void* a, const void* b);
		static int compareZ(const void* a, const void* b);
	};

	//! Sphere
	SGLCLASS BoundingSphere
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

	/**
		Tests intersections of Bounding objects
	*/
	SGLCLASS Intersector
	{
	public:
		static bool intersectRaySphere(Ray ray, BoundingSphere sphere);
		static bool intersectRayBox(Ray ray, BoundingBox bbox);
	};
};

#endif
