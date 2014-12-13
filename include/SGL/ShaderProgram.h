
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

		/**
			load the shader program from to files
		*/
		bool loadFromFile(std::string vertSource, std::string fragSource);

		/**
			Create the program directly
		*/
		bool createProgram(const GLchar*[], const GLchar*[]);

		/**
			Remove the shader from opengl
		*/
		bool freeProgram();

		/**
			bind the shader program
		*/
		bool bind();
		/**
			Unbind the shader program
		*/
		void unbind();

		/**
			Start using the Shader
		*/
		void begin();
		/**
			Stop using shader
		*/
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
		//! program handle
		GLuint _programID;
		//! vertex shader handle
		GLuint _vertexShader;
		//! fragment shader handle
		GLuint _fragmentShader;

		//! store attributes
		std::map<std::string, VertexAttribute>* _attributes;

		/**
			Print the Log for this program
		*/
		void printProgramLog(GLuint);

		/**
			Print the log for a specigic shader
		*/
		void printShaderLog(GLuint);

		int _numAttributes;

	};

};

