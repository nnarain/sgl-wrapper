
#include "SGL/Util/ObjModel.h"

using namespace sgl;

ObjModel::ObjModel() :
	_mesh(Mesh::Type::TRIANGLES, Buffer::Usage::STATIC_DRAW),
	_meshData(new std::map<std::string, MeshData>),
	_meshDataKeys(new std::vector<std::string>),
	_vertexCount(0),
	_texture(Texture::Target::TEXTURE2D)
{
}

void ObjModel::bind(Texture::Unit unit)
{
	_texture.bind(unit);
	bind();
}

void ObjModel::bind()
{
	_mesh.bind();
}

void ObjModel::draw()
{
	_mesh.draw();
}

void ObjModel::unbind()
{
	_mesh.unbind();
}

void ObjModel::addMeshData(const std::string &name, int offset, int vertexCount)
{
	MeshData data;
	data.drawCount = vertexCount;
	data.offset = offset;

	(*_meshData)[name] = data;
	_meshDataKeys->push_back(name);

	_vertexCount += vertexCount;
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

Texture& ObjModel::getTexture()
{
	return _texture;
}

ObjModel::~ObjModel()
{
	delete _meshData;
	delete _meshDataKeys;
}