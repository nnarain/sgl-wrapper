#include "SGL/Wrapper/ShaderProgram.h"

#include "SGL/Util/Exception.h"

#include <fstream>
#include <cassert>

using namespace sgl;

bool ShaderProgram::_inUse = false;

ShaderProgram::ShaderProgram(void) :
	_vertexShader(0),
	_fragmentShader(0),
	_attributeLocation(0),
	_attributes(new std::vector<VertexAttribute>),
	_isActive(false)
{
	create();
}

void ShaderProgram::create()
{
	// allocate space for a shader program
	_programID = glCreateProgram();
}

void ShaderProgram::bind()
{
	// use this shader's ID
	glUseProgram(_programID);

	// Get any errors
	GLenum error = glGetError();
	if (error != GL_NO_ERROR){
		throw Exception(getProgramLog());
	}
}

void ShaderProgram::unbind()
{
	// use default program
	glUseProgram(0);
}

void ShaderProgram::begin()
{
	assert(!_isActive && !_inUse && "This or another shader is already bound!!");

	bind();
	_isActive = _inUse = true;
}

void ShaderProgram::end()
{
	assert(_isActive && _inUse && "Cannot terminate inactive shader");

	unbind();
	_isActive = _inUse = false;
}

bool ShaderProgram::link()
{
	glLinkProgram(_programID);

	GLint success;
	glGetProgramiv(_programID, GL_LINK_STATUS, &success);

	if (success != GL_TRUE){
		throw Exception(getProgramLog());
	}

	return true;
}

void ShaderProgram::addAttribute(const std::string &name, int numComponents)
{
	glBindAttribLocation(_programID, _attributeLocation, name.c_str());

	_attributes->emplace_back(_attributeLocation++, numComponents);
	//_attributeLocation++;
}

void ShaderProgram::addAttribute(const std::string &name, int numComponents, int numComponentsPerLocations)
{
	glBindAttribLocation(_programID, _attributeLocation, name.c_str());

	_attributeLocation += numComponents / numComponentsPerLocations;

	_attributes->emplace_back(_attributeLocation, numComponents);
}

void ShaderProgram::loadFromFile(const std::string &vertSource, const std::string &fragSource)
{
	// load the vertex and fragment shaders from a file pointed to by the strings
	loadFromFile(Type::VERTEX, vertSource);
	loadFromFile(Type::FRAGMENT, fragSource);
}

void ShaderProgram::loadFromFile(Type shaderType, const std::string & filename)
{
	// open the file
	std::ifstream file(filename.c_str());

	if (!file.good())
	{
		char *buff = new char[filename.length() + 40];
		sprintf(buff, "SGL Error: File \"%s\" could not be found", filename.c_str());
		std::string message(buff);
		delete[]buff;
		throw Exception(message);
	}

	std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	load(shaderType, source);
}

void ShaderProgram::load(Type shaderType, const std::string & source)
{
	// set which shader handle to set
	GLuint * shader;
	switch (shaderType)
	{
	case Type::VERTEX:
		shader = &_vertexShader;
		break;
	case Type::FRAGMENT:
		shader = &_fragmentShader;
		break;
	default:
		throw Exception("Invalid Shader Type");
		break;
	}

	// allocate a shader
	*shader = glCreateShader(static_cast<GLuint>(shaderType));

	// set the shader source
	const GLchar * shaderSrc[] = { source.c_str() };
	glShaderSource(*shader, 1, shaderSrc, NULL);

	// compile the shader
	glCompileShader(*shader);

	// check compile status
	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &shaderCompiled);

	if (shaderCompiled != GL_TRUE)
	{
		std::string log = getShaderLog(*shader);
		throw Exception(log);
	}

	// attach the shader to the program
	glAttachShader(_programID, *shader);
}

void ShaderProgram::attribute(const std::string &name, glm::vec3 v)
{
	glUniform3f(getAttributeLocation(name), v.x, v.y, v.z);
}

Uniform ShaderProgram::uniform(const std::string &name)
{
	return Uniform(getUniformLocation(name));
}

GLuint ShaderProgram::getAttributeLocation(const std::string &name)
{
	return glGetAttribLocation(_programID, name.c_str());
}

GLint ShaderProgram::getUniformLocation(const std::string &name)
{
	return glGetUniformLocation(_programID, name.c_str());
}

const std::vector<VertexAttribute> & ShaderProgram::getVertexAttributes() const
{
	return (*_attributes);
}

GLuint ShaderProgram::handle() const
{
	return _programID;
}

std::string ShaderProgram::getProgramLog()
{
	// get length
	int len;
	int logLength;
	glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &len);

	char* log = new char[len];
	glGetProgramInfoLog(_programID, len, &logLength, log);

	if (logLength > 0)
	{
		std::string message(log);
		delete[] log;

		return message;
	}
	else
	{
		std::string message("Nothing here");
		delete[] log;
		return message;
	}
}

std::string ShaderProgram::getShaderLog(GLuint shader)
{
	int len;
	int lenLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

	char* log = new char[len];

	glGetShaderInfoLog(shader, len, &lenLog, log);

	std::string message(log);
	delete[] log;

	return message;
}

void ShaderProgram::destroy()
{
	if (_vertexShader != 0)
	{
		glDetachShader(_programID, _vertexShader);
		glDeleteShader(_vertexShader);
	}

	if (_fragmentShader != 0)
	{
		glDetachShader(_programID, _fragmentShader);
		glDeleteShader(_fragmentShader);
	}
	
	if (_programID != 0)
	{
		glDeleteProgram(_programID);
	}
}

Uniform ShaderProgram::operator[](const std::string &name)
{
	return uniform(name);
}

ShaderProgram::~ShaderProgram(void)
{
	destroy();
	delete _attributes;
}