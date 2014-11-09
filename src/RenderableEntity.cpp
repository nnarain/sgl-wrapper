#include "RenderableEntity.h"

using namespace sgl;

RenderableEntity::RenderableEntity()
{

}

void RenderableEntity::setVertexAttributeSet(VertexAttributeSet *set)
{
	_attribs = set;
}


RenderableEntity::~RenderableEntity(void)
{

}
