
#pragma once

#ifndef MESHGENERATOR_H
#define MESHGENERATOR_H

#include "SGL/SGLExport.h"
#include "SGL/Mesh.h"

// math
#include <glm/vec3.hpp>

namespace sgl
{
	struct Triangle
	{
		glm::vec3 v1;
		glm::vec3 v2;
		glm::vec3 v3;
	};

	struct Line
	{
		glm::vec3 p1;
		glm::vec3 p2;

		Line(glm::vec3 a, glm::vec3 b)
		{
			p1 = a;
			p2 = b;
		}
	};

	SGLVOIDFUNC generateCubeMesh(Mesh* mesh, float scale);
	SGLVOIDFUNC generateSphereMesh(Mesh* mesh, float scale);

	SGLVOIDFUNC generateWireframe(Mesh* mesh, void* buffer, int size, int stride);
	SGLVOIDFUNC generateCubeWireframe(Mesh* mesh);
	SGLVOIDFUNC generateSphereWireframe(Mesh* mesh);
};

#endif
