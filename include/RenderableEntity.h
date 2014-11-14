#pragma once

#include <vector>

#include "Entity.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Material.h"

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

		void setModel(Model* set);
		
		void setMaterial(Material material);
		Material* getMaterial();

	private:
		Model *_model;
		Material _material;
		
	};

};