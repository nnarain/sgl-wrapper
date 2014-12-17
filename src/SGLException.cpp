
#include "SGL/SGLException.h"

static sgl::SGLErrorCallback _sglError;

void sgl::setErrorCallback(SGLErrorCallback callback)
{
	_sglError = callback;
}

void sgl::sglCheckGLError()
{
	GLenum error = glGetError();
	std::string what;

	if (error != GL_NO_ERROR)
	{
		switch (error)
		{
		case GL_INVALID_ENUM:
			what =  "invalid enum";
			break;
		case GL_INVALID_VALUE:
			what = "invalid value";
			break;
		case GL_INVALID_OPERATION:
			what = "invalid operation";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			what = "invalid frame buffer";
			break;
		case GL_OUT_OF_MEMORY:
			what = "out of memeory";
			break;
		case GL_STACK_UNDERFLOW:
			what = "stack underflow";
			break;
		case GL_STACK_OVERFLOW:
			what = "stack overflow";
			break;
		}

		sglReportError(what);
	}
}

void sgl::sglReportError(std::string what)
{
	if (_sglError != NULL) _sglError(what);
}

