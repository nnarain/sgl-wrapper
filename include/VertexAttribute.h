

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

		//void createBuffer(void * data, int numElements, int numComponents, int componentSize);
		void bind();

		//std::string getName() const;
		GLuint getLocation() const;
		int getNumElements() const;
		int getNumComponents() const;
		int getSizeComponents() const;

	private:
		//std::string _attrName;
		GLuint _loc;
		int _numElements;
		int _numComponents;
		int _sizeComponent;

		GLuint id;

	};
};



#endif
