
#pragma once

#ifndef GLBUFFER_H
#define GLBUFFER_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <GL/glew.h>

namespace sgl
{
#ifdef _MSC_VER
	class DLLEXPORT IGLBuffer
#else
	class IGLBuffer
#endif
	{
	public:
		IGLBuffer(GLuint defaultTarget);
		~IGLBuffer();

		void bind(GLuint target);
		void bind();
		void unbind();

		GLuint handle() const;

	protected:
		GLuint _id;

		GLuint _defaultTarget;
		GLuint _currentTarget;

		bool _isBound;
	};
};

#endif
