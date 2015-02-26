
/**
	Handle a Shader Program

	@author Natesh Narain
*/

#pragma once

#include <GL/glew.h>

#include "SGL/Util/SGLExport.h"
#include "SGL/Wrapper/VertexAttribute.h"
#include "SGL/Wrapper/Uniform.h"
#include "SGL/Util/Exception.h"


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

		/* Types */
		enum class Type
		{
			VERTEX   = GL_VERTEX_SHADER,
			FRAGMENT = GL_FRAGMENT_SHADER
		};

		/* Load Shader program in various ways */

		void load(Type shader, const std::string &source);

		void loadFromFile(Type shader, const std::string & file);

		/**
			load the shader program from to files
		*/
		void loadFromFile(const std::string& vertSource, const std::string& fragSource);

		/**
			bind the shader program
		*/
		void bind();
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

		/**
			@return the uniform specified by the name

			@param name
				Name of Uniform
		*/
		Uniform uniform(const std::string &name);

		/**
			Get the specified vertex attribute location
		*/
		GLuint getAttributeLocation(const std::string &name);
		/**
			Get the specified uniform location from the shader
		*/
		GLint getUniformLocation(const std::string &name);

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
		std::string getProgramLog();

		/**
			Print the log for a specigic shader
		*/
		std::string getShaderLog(GLuint);

		void create();
		/**
			Remove the shader from opengl
		*/
		void destroy();

	};

};

