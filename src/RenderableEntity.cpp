#include "RenderableEntity.h"

using namespace sgl;

const char* RenderableEntity::POSITION = "a_position";
const char* RenderableEntity::NORMAL = "a_normal";

RenderableEntity::RenderableEntity()
{
	_attributes = new std::vector<VertexAttribute*>();
	_indices = new std::vector<IndexBufferObject*>();
}

void RenderableEntity::addVertexAttribute(VertexAttribute *attr)
{
	_attributes->push_back(attr);
}

void RenderableEntity::addIndexBufferObject(IndexBufferObject *ibo)
{
	_indices->push_back(ibo);
}

AttributeIterator RenderableEntity::getAttributeStart() const
{
	return _attributes->begin();
}

AttributeIterator RenderableEntity::getAttributeEnd() const
{
	return _attributes->end();
}

IndexIterator RenderableEntity::getIndexStart() const
{
	return _indices->begin();
}

IndexIterator RenderableEntity::getIndexEnd() const
{
	return _indices->end();
}

RenderableEntity::~RenderableEntity(void)
{
	// delete attributes
	AttributeIterator iter;
	for (iter = _attributes->begin(); iter != _attributes->end(); ++iter)
	{
		delete *iter;
	}
	delete _attributes;

	// delete index buffers
	IndexIterator iboIter;
	for (iboIter = _indices->begin(); iboIter != _indices->end(); ++iboIter)
	{
		delete *iter;
	}
	delete _indices;
}
