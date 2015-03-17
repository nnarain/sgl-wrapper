
#include "SGL/Util/ObjLoader.h"

#include <SGL/Util/Exception.h>

#include <fstream>

using namespace sgl;

ObjLoader::ObjLoader() : 
	_positions(new std::vector<glm::vec3>),
	_normals(new std::vector<glm::vec3>),
	_texCoords(new std::vector<glm::vec3>)
{
}

void ObjLoader::load(ObjModel &model, const std::string &filename)
{
	std::ifstream file(filename);

	if (!file.good())
		throw Exception("could not open file: " + filename);

	//
	int offset = 0;
	int vertexperMesh = 0;
}

ObjLoader::~ObjLoader()
{
	delete _positions;
	delete _normals;
	delete _texCoords;
}
