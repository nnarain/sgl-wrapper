
#include "SGL/SGLException.h"

using namespace sgl;

SGLException::SGLException() :
	_msg(new std::string("An opengl error occurred"))
{
}

SGLException::SGLException(const std::string& what) :
	_msg(new std::string(what))
{
}

const char *SGLException::what() const throw()
{
	return _msg->c_str();
}

SGLException::~SGLException()
{
	delete _msg;
}