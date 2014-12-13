
/**
	Interface for an error callback system

	@author Natesh Narain
*/

#pragma once

#ifndef SGLEXCEPTION_H
#define SGLEXCEPTION_H

#include "SGLExport.h"

#include <GL/glew.h>
#include <string>

namespace sgl
{
	typedef void(*SGLErrorCallback)(std::string what);

	SGLVOIDFUNC setErrorCallback(SGLErrorCallback callback);
	
	SGLVOIDFUNC sglCheckGLError();
	SGLVOIDFUNC sglReportError(std::string what);
};

#endif
