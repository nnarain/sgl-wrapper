
#include "SGL/Math/Frustum.h"

using namespace sgl;

Frustum::Frustum()
{
}

Plane& Frustum::getPlane(PlaneId id)
{
	return _planes[static_cast<int>(id)];
}

Frustum::~Frustum()
{

}
