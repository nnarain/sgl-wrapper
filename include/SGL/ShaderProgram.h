
/**
	Handle a Shader Program

	@author Natesh Narain
*/

#pragma once

#include <GL/glew.h>

#include "SGLExport.h"

#include "VertexAttribute.h"
#include "Mesh.h"
#include "SGLException.h"

#include <glm/glm.hpp>

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

	private:
		ShaderProgram(const ShaderProgram&);
		ShaderProgram& operator=(const ShaderProgram&);

	public:

		/* Load Shader program in various ways */

		bool load(GLuint shader, const std::string &source);

		bool loadFromFile(GLuint shader, const std::string & file);

		/**
			load the shader program from to files
		*/
		bool loadFromFile(const std::string& vertSource, const std::string& fragSource);

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
		void addAttribute(const std::string &name, int numComponents);
		void addAttribute(const std::string &name, int numComponents, int numComponentsPerLocations);

		/* Passes the value the corresponding attribute in the shader */

		void attribute(const std::string &name, glm::vec3 value);

		/* Passes the value to the corresponding uniform in the shader */

		void uniform(const std::string &name, glm::mat3 value);
		void uniform(const std::string &name, glm::mat4 value);

		void uniform(const std::string &name, glm::vec3 value);
		void uniform(const std::string &name, glm::vec4 value);

		void uniform(const std::string &name, int value);

		void uniform(const std::string &name, float value);

		/**
			Get the specified vertex attribute location
		*/
		GLuint getAttributeLocation(const std::string &name);
		/**
			Get the specified uniform location from the shader
		*/
		GLuint getUniformLocation(const std::string &name);

		/**
			@return vector containing vertex attributes
		*/
		const std::vector<VertexAttribute> & getVertexAttributes() const;

		/**
			@return the program handle
		*/
		GLuint handle() const;

	private:
		//! program handle
		GLuint _programID;
		//! vertex shader handle
		GLuint _vertexShader;
		//! fragment shader handle
		GLuint _fragmentShader;

		//! attribute location
		int _attributeLocation;

		//! store attributes
		std::vector<VertexAttribute>* _attributes;

		//! is active flag for this object
		bool _isActive;
		//! flag checks if any shader is active
		static bool _inUse;

		/**
			Print the Log for this program
		*/
		void printProgramLog(GLuint);

		/**
			Print the log for a specigic shader
		*/
		void printShaderLog(GLuint);

		/**
			Remove the shader from opengl
		*/
		bool freeProgram();

	};

};

