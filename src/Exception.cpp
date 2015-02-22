
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

Exception::~Exception()
{
	delete _msg;
}