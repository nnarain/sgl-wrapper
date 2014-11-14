#pragma once

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <string>
#include <GL/glew.h>
#include "Camera.h"
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace sgl{

#ifdef _MSC_VER
	class DLLEXPORT ShaderProgram
#else
	class ShaderProgram
#endif
	{
	public:

		ShaderProgram(void);
		virtual ~ShaderProgram(void);

		bool createProgram(const GLchar*[], const GLchar*[]);
		bool freeProgram();

		bool bind();
		void unbind();

		void begin();
		void end();

		bool link();

		void addAttribute(const std::string name);

		void attribute(std::string name, glm::vec3);

		void uniform(std::string name, glm::mat4);
		void uniform(std::string name, glm::mat3);
		void uniform(std::string name, glm::vec3);
		void uniform(std::string name, glm::vec4);

		GLuint getAttributeLocation(std::string name);
		GLuint getUniformLocation(std::string name);

	private:
		void enableAttr();
		void disableAttr();

	protected:

		GLuint mProgramID;
		GLuint mVertexShader;
		GLuint mFragmentShader;


		void printProgramLog(GLuint);
		void printShaderLog(GLuint);

		int numAttributes;

		//glm::mat4 proj;
		//glm::mat4 view;
		//glm::mat4 projView;

	};

};

