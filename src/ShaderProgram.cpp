#include "SGL/ShaderProgram.h"

#include "SGL/SGLException.h"

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
	// allocate space for a shader program
	_programID = glCreateProgram();
}

bool ShaderProgram::bind()
{
	// use this shader's ID
	glUseProgram(_programID);

	// Get any errors
	GLenum error = glGetError();
	if (error != GL_NO_ERROR){
		printProgramLog(_programID);
		return false;
	}

	return true;
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
		printProgramLog(_programID);
		return false;
	}

	return true;
}

void ShaderProgram::addAttribute(const std::string &name, int numComponents)
{
	glBindAttribLocation(_programID, _attributeLocation, name.c_str());

	_attributeLocation++;

	_attributes->emplace_back(_attributeLocation, numComponents);
}

void ShaderProgram::addAttribute(const std::string &name, int numComponents, int numComponentsPerLocations)
{
	glBindAttribLocation(_programID, _attributeLocation, name.c_str());

	_attributeLocation += numComponents / numComponentsPerLocations;

	_attributes->emplace_back(_attributeLocation, numComponents);
}

bool ShaderProgram::loadFromFile(const std::string &vertSource, const std::string &fragSource)
{
	// load the vertex and fragment shaders from a file pointed to by the strings
	return loadFromFile(GL_VERTEX_SHADER, vertSource) && loadFromFile(GL_FRAGMENT_SHADER, fragSource);
}

bool ShaderProgram::loadFromFile(GLuint shaderType, const std::string & filename)
{
	// open the file
	std::ifstream file(filename.c_str());

	if (!file.good()) return false;

	std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	bool ret = load(shaderType, source);

	file.close();

	return ret;
}

bool ShaderProgram::load(GLuint shaderType, const std::string & source)
{
	assert(shaderType == GL_VERTEX_SHADER || shaderType == GL_FRAGMENT_SHADER && "Invalid argument");

	// set which shader handle to set
	GLuint * shader;
	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
		shader = &_vertexShader;
		break;
	case GL_FRAGMENT_SHADER:
		shader = &_fragmentShader;
		break;
	}

	// allocate a shader
	*shader = glCreateShader(shaderType);

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
		printShaderLog(*shader);
		return false;
	}

	// attach the shader to the program
	glAttachShader(_programID, *shader);

	return true;
}

void ShaderProgram::attribute(const std::string &name, glm::vec3 v)
{
	glUniform3f(getAttributeLocation(name), v.x, v.y, v.z);
}

void ShaderProgram::uniform(const std::string &name, glm::mat3 m)
{
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::uniform(const std::string &name, glm::mat4 m)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::uniform(const std::string &name, glm::vec3 v)
{
	glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
}

void ShaderProgram::uniform(const std::string &name, glm::vec4 v)
{
	glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
}

void ShaderProgram::uniform(const std::string &name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void ShaderProgram::uniform(const std::string &name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

GLuint ShaderProgram::getAttributeLocation(const std::string &name)
{
	return glGetAttribLocation(_programID, name.c_str());
}

GLuint ShaderProgram::getUniformLocation(const std::string &name)
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

void ShaderProgram::printProgramLog(GLuint program)
{
	if (glIsProgram(program)){
		// get length
		int len;
		int logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		char* log = new char[len];

		glGetProgramInfoLog(program, len, &logLength, log);
		if (logLength > 0){
			
		}

		delete[] log;
	}
	else{
		
	}
}

void ShaderProgram::printShaderLog(GLuint shader)
{
	if (glIsShader(shader)){

		int len;
		int lenLog;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		char* log = new char[len];

		glGetShaderInfoLog(shader, len, &lenLog, log);
		if (lenLog > 0){
			
		}

		delete[] log;

	}
	else{
		
	}
}

bool ShaderProgram::freeProgram()
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
	
	return true;
}


ShaderProgram::~ShaderProgram(void)
{
	freeProgram();

	delete _attributes;
}