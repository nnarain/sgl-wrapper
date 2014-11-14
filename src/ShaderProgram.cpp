#include "ShaderProgram.h"

#include <iostream>

using namespace sgl;

ShaderProgram::ShaderProgram(void)
{
	mProgramID = NULL;
	numAttributes = 0;
}

bool ShaderProgram::bind()
{
	// use this shader's ID
	glUseProgram(mProgramID);

	// Get any errors
	GLenum error = glGetError();
	if (error != GL_NO_ERROR){
		std::cout << "Error binding program" << std::endl;
		printProgramLog(mProgramID);
		return false;
	}

	return true;
}

void ShaderProgram::unbind()
{
	// use default program
	glUseProgram(NULL);
}

void ShaderProgram::begin()
{
	bind();
//	enableAttr();
}

void ShaderProgram::end()
{
//	disableAttr();
	unbind();
}

bool ShaderProgram::link()
{
	glLinkProgram(mProgramID);

	GLint success;
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &success);

	if (success != GL_TRUE){
		std::cout << "Error linking program " << mProgramID << std::endl;
		printProgramLog(mProgramID);
		return false;
	}

	return true;
}

void ShaderProgram::addAttribute(const std::string name)
{
	glBindAttribLocation(mProgramID, numAttributes++, name.c_str());
}

void ShaderProgram::enableAttr()
{
	// enable attributes
	int i;
	for (i = 0; i < numAttributes; i++){
		glEnableVertexAttribArray(i);
	}
}

void ShaderProgram::disableAttr()
{
	int i;
	for (i = 0; i < numAttributes; i++){
		glDisableVertexAttribArray(i);
	}
}

bool ShaderProgram::createProgram(const GLchar* vs[], const GLchar* fs[])
{
	// allocate space for a shader program
	mProgramID = glCreateProgram();

	// get the vertex shader source
	mVertexShader = glCreateShader(GL_VERTEX_SHADER);

	// set the shader source
	glShaderSource(mVertexShader, 1, vs, NULL);

	// verify shader
	glCompileShader(mVertexShader);

	// check shader errors
	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &shaderCompiled);

	if (shaderCompiled != GL_TRUE){
		std::cout << "Unable to compile vertex shader" << std::endl;
		printShaderLog(mVertexShader);
		return false;
	}

	// attach the compiled vertex shader
	glAttachShader(mProgramID, mVertexShader);

	// get the fragmenet shader source
	mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// set frag shader soource
	glShaderSource(mFragmentShader, 1, fs, NULL);

	glCompileShader(mFragmentShader);

	shaderCompiled = GL_FALSE;
	glGetShaderiv(mFragmentShader, GL_COMPILE_STATUS, &shaderCompiled);

	if (shaderCompiled != GL_TRUE){
		std::cout << "Unable to compile fragment shader" << std::endl;
		printShaderLog(mFragmentShader);
		return false;
	}

	glAttachShader(mProgramID, mFragmentShader);

	return true;
}

bool ShaderProgram::freeProgram()
{
	glDetachShader(mProgramID, mVertexShader);
	glDetachShader(mProgramID, mFragmentShader);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);
	glDeleteProgram(mProgramID);
	return true;
}

void ShaderProgram::attribute(std::string name, glm::vec3 v)
{
	glUniform3f(getAttributeLocation(name), v.x, v.y, v.z);
}

void ShaderProgram::uniform(std::string name, glm::mat3 m)
{
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::uniform(std::string name, glm::mat4 m)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::uniform(std::string name, glm::vec3 v)
{
	glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
}

void ShaderProgram::uniform(std::string name, glm::vec4 v)
{
	glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
}

GLuint ShaderProgram::getAttributeLocation(std::string name)
{
	return glGetAttribLocation(mProgramID, name.c_str());
}

GLuint ShaderProgram::getUniformLocation(std::string name)
{
	return glGetUniformLocation(mProgramID, name.c_str());
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
			std::cout << log << std::endl;
		}

		delete[] log;

	}
	else{
		std::cout << "Invalid program ID" << std::endl;
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
			std::cout << log << std::endl;
		}

		delete[] log;

	}
	else{
		std::cout << "Invalid shader ID" << std::endl;
	}
}

ShaderProgram::~ShaderProgram(void)
{
	freeProgram();
}