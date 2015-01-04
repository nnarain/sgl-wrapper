
/**
	Handle a Shader Program

	@author Natesh Narain
*/

#pragma once

#include <GL/glew.h>

#include "SGLExport.h"

#include "VertexAttribute.h"
#include "Mesh.h"

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <string>
#include <vector>

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

		/**
			Creates and adds a vertex attribute to the shader, binding its location in the order that this function is called.
			Locations start at 0
		*/
		void addAttribute(const std::string name, int numComponents);
		
		/**
			Associates the given mesh with this shader.
			Meaning that the given mesh contains the corresponding shader attributes
		*/
		void assoicateMesh(Mesh* mesh);

		/* Passes the value the corresponding attribute in the shader */

		void attribute(std::string name, glm::vec3 value);

		/* Passes the value to the corresponding uniform in the shader */

		void uniform(std::string name, glm::mat3 value);
		void uniform(std::string name, glm::mat4 value);
		void uniform(std::string name, glm::vec3 value);
		void uniform(std::string name, glm::vec4 value);

		void uniform(std::string name, int value);

		/**
			Get the specified vertex attribute location
		*/
		GLuint getAttributeLocation(std::string name);
		/**
			Get the specified uniform location from the shader
		*/
		GLuint getUniformLocation(std::string name);

	protected:
		//! program handle
		GLuint _programID;
		//! vertex shader handle
		GLuint _vertexShader;
		//! fragment shader handle
		GLuint _fragmentShader;

		//! store attributes
		std::vector<VertexAttribute>* _attributes;

		//! is active flag
		bool _isActive;

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

