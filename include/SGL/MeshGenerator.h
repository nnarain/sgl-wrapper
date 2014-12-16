
#pragma once

#ifndef MESHGENERATOR_H
#define MESHGENERATOR_H

#include "SGL/SGLExport.h"
#include "SGL/Mesh.h"

namespace sgl
{
	SGLVOIDFUNC generateCubeMesh(Mesh* mesh, float scale);
	SGLVOIDFUNC generateSphereMesh(Mesh* mesh, float scale);
};

#endif
