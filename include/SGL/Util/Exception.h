
/**
	Interface for an error callback system

	@author Natesh Narain
*/

#pragma once

#ifndef SGLEXCEPTION_H
#define SGLEXCEPTION_H


#include <GL/glew.h>
#include "SGLExport.h"

#include <stdexcept>
#include <string>

namespace sgl
{
	SGLCLASS Exception : public std::runtime_error
	{
	public:
		Exception();
		Exception(const std::string& what);
		Exception(const char *what);
		~Exception();

		static void glerror(const std::string&);
	};
};

#endif
