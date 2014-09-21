#pragma once

#ifndef STATICMODEL_H
#define STATICMODEL_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <GL/glew.h>

namespace sgl{
	
#ifdef _MSC_VER
	class DLLEXPORT StaticModel
#else
	class StaticModel
#endif
	{
	public:
		StaticModel();
		~StaticModel();

		void bindVBO(float *vertexBuffer, int len);
		void bindIBO(int *indexBuffer, int index, int len);

		void setNumMeshes(int);

		GLuint getVBO() const;
		GLuint getIBO(int idx) const;
		int getNumberOfIndices(int idx) const;
		int getNumberOfMeshes() const;

	private:
		GLuint vbo;
		GLuint *ibos;

		int numMeshes;
		int *numIndices;

	};

};

#endif