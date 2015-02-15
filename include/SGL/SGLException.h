
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
	SGLCLASS SGLException : public std::exception
	{
	public:
		SGLException();
		SGLException(const std::string& what);
		SGLException(const char *what);
		~SGLException();

		const char *what() const throw();
	private:
		std::string * _msg;
	};
};

#endif
