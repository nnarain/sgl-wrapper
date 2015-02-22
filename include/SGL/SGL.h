
/**
	Include primary parts of API

	@author Natesh Narain
*/

#pragma once

#ifndef SGL_H
#define SGL_H

#include <GL/glew.h>

#include "Camera.h"
#include "ShaderProgram.h"
#include "Entity.h"

#include "SpriteBatch.h"
#include "Sprite.h"
#include "SpriteSheet.h"

#include "Mesh.h"
#include "InstanceMesh.h"

#include "Texture.h"

#include "Exception.h"

#include "SGLCoordinate.h"

#include "SGLExport.h"

namespace sgl
{
	SGLBOOLFUNC init();
};

#endif
