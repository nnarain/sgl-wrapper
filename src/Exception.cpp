
#include "SGL/Exception.h"

using namespace sgl;

Exception::Exception() :
	_msg(new std::string("An opengl error occurred"))
{
}

Exception::Exception(const std::string& what) :
	_msg(new std::string(what))
{
}

Exception::Exception(const char *what) :
	_msg(new std::string(what))
{
}

const char *Exception::what()
{
	return _msg->c_str();
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
	delete _msg;
}