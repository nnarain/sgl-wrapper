
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
#include "Model.h"

#include "Texture.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"

#include "Material.h"

#include "Intersector.h"

#include "SGLException.h"

namespace sgl
{
	bool init()
	{
		// init glew
		glewExperimental = true;
		if (glewInit() != GLEW_OK){
			return false;
		}

		// set error callback to null
		setErrorCallback(NULL);

		return true;
	}
};

#endif
