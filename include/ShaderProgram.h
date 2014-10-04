#pragma once

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <string>
#include <GL/glew.h>
#include "Camera.h"
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

		void begin(Camera& camera);
		void end();

		bool link();

		void addAttribute(const std::string name);

		GLuint getAttributeLocation(std::string name);
		GLuint getUniformLocation(std::string name);

		glm::mat4 getProjectionView();
		glm::mat4 getProjectionMatri();
		glm::mat4 getViewMatrix();

	private:
		void enableAttr();
		void disableAttr();

	protected:
		void printProgramLog(GLuint);
		void printShaderLog(GLuint);

		GLuint mProgramID;
		GLuint mVertexShader;
		GLuint mFragmentShader;

		int numAttributes;

		glm::mat4 proj;
		glm::mat4 view;
		glm::mat4 projView;

	};

};

