
#pragma once

#ifndef MESHGENERATOR_H
#define MESHGENERATOR_H

#include "SGL/SGLExport.h"
#include "SGL/Mesh.h"
#include "Geometry.h"

// math
#include <glm/vec3.hpp>

namespace sgl
{


	SGLVOIDFUNC generateCubeMesh(Mesh* mesh, float scale);
	SGLVOIDFUNC generateSphereMesh(Mesh* mesh, float scale);

	SGLVOIDFUNC generateWireframe(Mesh* mesh, void* buffer, int size, int stride);
	SGLVOIDFUNC generateCubeWireframe(Mesh* mesh);
	SGLVOIDFUNC generateSphereWireframe(Mesh* mesh);
};

#endif
