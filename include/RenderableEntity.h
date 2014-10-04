#pragma once

#include <vector>

#include "Entity.h"
#include "ShaderProgram.h"
#include "StaticModel.h"
#include "VertexAttribute.h"
#include "IndexBufferObject.h"

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

		const static char* POSITION;
		const static char* NORMAL;

		RenderableEntity(void);
		~RenderableEntity(void);

		virtual void render(ShaderProgram& shader) = 0;

		void addVertexAttribute(VertexAttribute* attr);
		void addIndexBufferObject(IndexBufferObject* ibo);

		AttributeIterator getAttributeStart() const;
		AttributeIterator getAttributeEnd() const;

		IndexIterator getIndexStart() const;
		IndexIterator getIndexEnd() const;

	private:
		std::vector<VertexAttribute*>* _attributes;
		std::vector<IndexBufferObject*>* _indices;

	};

};