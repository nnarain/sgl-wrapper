#include "SGL/ShaderProgram.h"

#include "SGL/SGLException.h"

#include <fstream>
#include <cassert>

using namespace sgl;

bool ShaderProgram::_inUse = false;

ShaderProgram::ShaderProgram(void)
{
	_programID = 0;
	_attributeLocation = 0;

	_attributes = new std::vector < VertexAttribute > ();

	_isActive = false;
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

void ShaderProgram::assoicateMesh(Mesh* mesh)
{
	int i;
	const int size = _attributes->size();

	// add the shader attributes to the mesh 
	for (i = 0; i < size; i++)
	{
		mesh->addAttribute((*_attributes)[i]);
	}
}

bool ShaderProgram::loadFromFile(const std::string &vertSource, const std::string &fragSource)
{
	std::ifstream fVertSource(vertSource.c_str());
	std::ifstream fFragSource(fragSource.c_str());

	if (!fVertSource.good() || !fFragSource.good())
	{
		sglReportError("shader file could not be found!");
		return false;
	}

	std::string vsContent((std::istreambuf_iterator<char>(fVertSource)), std::istreambuf_iterator<char>());
	std::string fsContent((std::istreambuf_iterator<char>(fFragSource)), std::istreambuf_iterator<char>());

	const GLchar* vs[] = { vsContent.c_str() };
	const GLchar* fs[] = { fsContent.c_str() };

	return createProgram(vs, fs);
}

bool ShaderProgram::createProgram(const GLchar* vs[], const GLchar* fs[])
{
	// allocate space for a shader program
	_programID = glCreateProgram();

	// get the vertex shader source
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// set the shader source
	glShaderSource(_vertexShader, 1, vs, NULL);

	// verify shader
	glCompileShader(_vertexShader);

	// check shader errors
	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &shaderCompiled);

	if (shaderCompiled != GL_TRUE){
		//std::cout << "Unable to compile vertex shader" << std::endl;
		printShaderLog(_vertexShader);
		return false;
	}

	// attach the compiled vertex shader
	glAttachShader(_programID, _vertexShader);

	// get the fragmenet shader source
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// set frag shader soource
	glShaderSource(_fragmentShader, 1, fs, NULL);

	glCompileShader(_fragmentShader);

	shaderCompiled = GL_FALSE;
	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &shaderCompiled);

	if (shaderCompiled != GL_TRUE){
		//std::cout << "Unable to compile fragment shader" << std::endl;
		printShaderLog(_fragmentShader);
		return false;
	}

	glAttachShader(_programID, _fragmentShader);

	return true;
}

bool ShaderProgram::freeProgram()
{
	glDetachShader(_programID, _vertexShader);
	glDetachShader(_programID, _fragmentShader);
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
	glDeleteProgram(_programID);
	return true;
}

void ShaderProgram::attribute(const std::string &name, glm::vec3 v)
{
	glUniform3f(getAttributeLocation(name), v.x, v.y, v.z);
	sglCheckGLError();
}

void ShaderProgram::uniform(const std::string &name, glm::mat3 m)
{
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
	sglCheckGLError();
}

void ShaderProgram::uniform(const std::string &name, glm::mat4 m)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
	sglCheckGLError();
}

void ShaderProgram::uniform(const std::string &name, glm::vec3 v)
{
	glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
	sglCheckGLError();
}

void ShaderProgram::uniform(const std::string &name, glm::vec4 v)
{
	glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
	sglCheckGLError();
}

void ShaderProgram::uniform(const std::string &name, int value)
{
	glUniform1i(getUniformLocation(name), value);
	sglCheckGLError();
}

GLuint ShaderProgram::getAttributeLocation(const std::string &name)
{
	return glGetAttribLocation(_programID, name.c_str());
}

GLuint ShaderProgram::getUniformLocation(const std::string &name)
{
	return glGetUniformLocation(_programID, name.c_str());
}

const VertexAttribute & ShaderProgram::getVertexAttribute(int idx) const
{
	return (*_attributes)[idx];
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
			sglReportError(std::string(log));
		}

		delete[] log;
	}
	else{
		sglReportError("Invalid program id");
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
			sglReportError(std::string(log));
		}

		delete[] log;

	}
	else{
		sglReportError("Invalid program id");
	}
}

ShaderProgram::~ShaderProgram(void)
{
	freeProgram();

	delete _attributes;
}