

#pragma once

#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

#include <string>
#include <GL/glew.h>

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif


namespace sgl{
#ifdef _MSC_VER
	class DLLEXPORT VertexAttribute
#else
	class VertexAttribute
#endif
	{
	public:

		VertexAttribute(GLuint loc, int numComponents);
		~VertexAttribute();

		//std::string getName() const;
		GLuint getLocation() const;
		int getNumComponents() const;


	private:
		GLuint _loc;
		int _numComponents;


		GLuint id;

	};
};



#endif
