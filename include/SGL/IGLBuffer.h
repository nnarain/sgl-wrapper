
#pragma once

#ifndef IGLBUFFER_H
#define IGLBUFFER_H

#include "SGLExport.h"

#include <GL/glew.h>

namespace sgl
{
	/**
		Generic interface to OpenGL buffer
	*/
	SGLCLASS IGLBuffer
	{
	public:

		IGLBuffer(GLuint defaultTarget);
		~IGLBuffer();

		virtual void bind(GLuint target);
		virtual void bind();
		virtual void unbind();

		void setDefaultTarget(GLuint target);

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
