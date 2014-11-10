#include "RenderableEntity.h"

using namespace sgl;

RenderableEntity::RenderableEntity()
{

}

void RenderableEntity::render()
{
	_attribs->bind();
	_attribs->draw();
	_attribs->unbind();
}

void RenderableEntity::setVertexAttributeSet(VertexAttributeSet *set)
{
	_attribs = set;
}


RenderableEntity::~RenderableEntity(void)
{

}
