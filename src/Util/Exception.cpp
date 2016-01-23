
#include "SGL/Util/Exception.h"

using namespace sgl;

Exception::Exception() : std::runtime_error("")
{
}

Exception::Exception(const std::string& what) : std::runtime_error(what)
{
}

Exception::Exception(const char *what) : std::runtime_error(what)
{
}

void Exception::glerror(const std::string& msg)
{
	GLenum error = glGetError();
	std::string what;

	if (error != GL_NO_ERROR)
	{
		switch (error)
		{
		case GL_INVALID_ENUM:
			what = "invalid enum: ";
			break;
		case GL_INVALID_VALUE:
			what = "invalid value: ";
			break;
		case GL_INVALID_OPERATION:
			what = "invalid operation: ";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			what = "invalid frame buffer: ";
			break;
		case GL_OUT_OF_MEMORY:
			what = "out of memeory: ";
			break;
		case GL_STACK_UNDERFLOW:
			what = "stack underflow: ";
			break;
		case GL_STACK_OVERFLOW:
			what = "stack overflow: ";
			break;
		default:
			what = "unknown: ";
			break;
		}

		throw Exception(what + msg);
	}
}

Exception::~Exception()
{
}