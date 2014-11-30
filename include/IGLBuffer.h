
#pragma once

#ifndef IGLBUFFER_H
#define IGLBUFFER_H

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

		virtual void bind(GLuint target);
		virtual void bind();
		virtual void unbind();

		GLuint handle() const;
		bool isBound() const;

	protected:
		GLuint* id();
		GLuint defaultTarget() const;
		GLuint currentTarget() const;

	private:
		GLuint _id;

		GLuint _defaultTarget;
		GLuint _currentTarget;

		bool _isBound;
	};
};

#endif
