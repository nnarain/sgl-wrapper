#include "RenderableEntity.h"

using namespace sgl;

RenderableEntity::RenderableEntity()
{
}

void RenderableEntity::render()
{
	_model->bind();
	_model->draw();
	_model->unbind();
}

void RenderableEntity::setModel(Model *aModel)
{
	_model = aModel;
}

void RenderableEntity::setMaterial(Material material)
{
	_material = material;
}

Material* RenderableEntity::getMaterial()
{
	return (&_material);
}

RenderableEntity::~RenderableEntity(void)
{

}
