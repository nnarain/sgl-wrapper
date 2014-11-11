#pragma once

#include <vector>

#include "Entity.h"
#include "ShaderProgram.h"
#include "VertexAttribute.h"
#include "Model.h"

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

		RenderableEntity(void);
		~RenderableEntity(void);

		virtual void render();

		void setVertexAttributeSet(Model* set);

	private:

	protected:
		sgl::Model *_attribs;

	};

};