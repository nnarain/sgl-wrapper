
/**
	Interface for an error callback system

	@author Natesh Narain
*/

#pragma once

#ifndef SGLEXCEPTION_H
#define SGLEXCEPTION_H


#include <GL/glew.h>
#include "SGLExport.h"

#include <exception>
#include <string>

namespace sgl
{
	SGLCLASS Exception : public std::exception
	{
	public:
		Exception();
		Exception(const std::string& what);
		Exception(const char *what);
		~Exception();

		const char *what();

		static void glerror(const std::string&);
	private:
		std::string * _msg;
	};
};

#endif
