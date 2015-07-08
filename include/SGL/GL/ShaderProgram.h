
/**
	Handle a Shader Program

	@author Natesh Narain
*/

#pragma once

#include <GL/glew.h>

#include "SGL/Util/SGLExport.h"
#include "SGL/GL/VertexAttribute.h"
#include "SGL/GL/Uniform.h"
#include "SGL/Util/Exception.h"

#include <string>
#include <vector>

namespace sgl{

	/**
		Encapsulates an OpenGL Shader Program
	*/
	SGLCLASS ShaderProgram
	{
		NO_COPY(ShaderProgram);

	public:
		ShaderProgram(void);
		virtual ~ShaderProgram(void);

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

		/**
			Link the shader
		*/
		void link();

		/**
			Creates and adds a vertex attribute to the shader, binding its location in the order that this function is called.
			Locations start at 0
		*/
		void addAttribute(const std::string &name);
		void bindFragOutput(const std::string name);

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
			@return the program handle
		*/
		GLuint handle() const;


		/* operators */
		Uniform operator[](const std::string &);

	private:
		//! program handle
		GLuint _programID;
		//! vertex shader handle
		GLuint _vertexShader;
		//! fragment shader handle
		GLuint _fragmentShader;

		//!
		int _attributeLocation;

		//!
		int _fragColorOutput;

		//! is active flag for this object
		bool _isActive;
		//!
		bool _isLinked;
		//!
		bool _isCompiled;
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

