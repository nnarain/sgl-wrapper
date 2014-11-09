#pragma once

#include <vector>

#include "Entity.h"
#include "ShaderProgram.h"
#include "VertexAttribute.h"
#include "IndexBufferObject.h"

#include "VertexAttributeSet.h"

#include <GL/glew.h>

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

namespace sgl{

	typedef std::vector<VertexAttribute*>::iterator AttributeIterator;
	typedef std::vector<IndexBufferObject*>::iterator IndexIterator;

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

		virtual void render(ShaderProgram& shader) = 0;

		void setVertexAttributeSet(VertexAttributeSet* set);

	private:

	protected:
		sgl::VertexAttributeSet *_attribs;

	};

};