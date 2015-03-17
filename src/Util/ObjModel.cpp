
#include "SGL/Util/ObjModel.h"

using namespace sgl;

ObjModel::ObjModel() :
	_mesh(Mesh::Type::TRIANGLES, Buffer::Usage::STATIC_DRAW),
	_meshData(new std::map<std::string, MeshData>),
	_meshDataKeys(new std::vector<std::string>)
{
}

void ObjModel::setMeshData(const std::string &name)
{
	MeshData &data = (*_meshData)[name];
	_mesh.setDrawStart(data.offset);
	_mesh.setDrawCount(data.drawCount);
}

void ObjModel::setMeshData(int idx)
{
	const std::string &name = (*_meshDataKeys)[idx];
	setMeshData(name);
}

Mesh& ObjModel::getMesh()
{
	return _mesh;
}

ObjModel::~ObjModel()
{
	delete _meshData;
	delete _meshDataKeys;
}