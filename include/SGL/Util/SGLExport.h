
/**
	Define export macros for different platforms

	@author Natesh Narain
*/

#pragma once

#ifndef SGLEXPORT_H
#define SGLEXPORT_H

// define class type if compiling on MSVC platform
#ifdef _MSC_VER
#	define DLLEXPORT __declspec(dllexport)
#	define SGLCLASS class DLLEXPORT
#	define SGLVOIDFUNC void DLLEXPORT
#	define SGLBOOLFUNC bool DLLEXPORT
#	define SGLFLOATFUNC float DLLEXPORT
#else
#	define SGLCLASS class
#	define SGLVOIDFUNC void
#	define SGLBOOLFUNC bool
#	define SGLFLOATFUNC float
#endif

#define NO_COPY(classname) \
	private: \
		classname(const classname&); \
		classname& operator=(classname);

#endif
