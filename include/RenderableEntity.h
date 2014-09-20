#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "StaticModel.h"

#include <GL/glew.h>

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

namespace sgl{

#ifdef _MSC_VER
	class DLLEXPORT RenderableEntity :
#else
	class RenderableEntity :
#endif
		public Entity
	{
	public:

		const static char* POSITION;
		const static char* NORMAL;

		RenderableEntity(StaticModel*);
		~RenderableEntity(void);

		void render(ShaderProgram* shader);

	private:
		StaticModel* model;

	};

};