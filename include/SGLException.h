
#pragma once

#ifndef SGLEXCEPTION_H
#define SGLEXCEPTION_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#ifdef DLLEXPORT
#define SGLVOIDFUNC void DLLEXPORT
#else
#define SGLVOIDFUNC void
#endif

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
