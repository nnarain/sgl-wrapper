#pragma once

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <string>
#include <GL/glew.h>
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

		void begin(glm::mat4 projView);
		void end();

		bool link();

		void addAttr(const std::string);

		GLuint getProgramID();
		glm::mat4 getProjectionView();

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

		glm::mat4 projView;

	};

};

