
/**
	Handle a Shader Program

	@author Natesh Narain
*/

#pragma once

#include <GL/glew.h>

#include "SGLExport.h"
#include "Camera.h"
#include "VertexAttribute.h"

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <string>
#include <map>

namespace sgl{

	/**
		Encapsulates an OpenGL Shader Program
	*/
	SGLCLASS ShaderProgram
	{
	public:

		ShaderProgram(void);
		virtual ~ShaderProgram(void);

		bool loadFromFile(std::string vertSource, std::string fragSource);
		bool createProgram(const GLchar*[], const GLchar*[]);
		bool freeProgram();

		bool bind();
		void unbind();

		void begin();
		void end();

		bool link();

		void addAttribute(const std::string name, int numComponents);
		VertexAttribute getAttribute(std::string name);

		void attribute(std::string name, glm::vec3);

		void uniform(std::string name, glm::mat4);
		void uniform(std::string name, glm::mat3);
		void uniform(std::string name, glm::vec3);
		void uniform(std::string name, glm::vec4);

		GLuint getAttributeLocation(std::string name);
		GLuint getUniformLocation(std::string name);

	protected:

		GLuint _programID;
		GLuint _vertexShader;
		GLuint _fragmentShader;

		std::map<std::string, VertexAttribute>* _attributes;

		void printProgramLog(GLuint);
		void printShaderLog(GLuint);

		int _numAttributes;

	};

};

