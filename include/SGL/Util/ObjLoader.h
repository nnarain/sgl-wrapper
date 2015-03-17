
#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <glm/glm.hpp>

#include <vector>
#include <map>

#include <SGL/Util/SGLExport.h>

#include <SGL/Util/ObjModel.h>

namespace sgl
{
	SGLCLASS ObjLoader
	{
	public:
		ObjLoader();
		~ObjLoader();

		void load(ObjModel &model, const std::string &filename);

	private:

		std::vector<glm::vec3> * _positions;
		std::vector<glm::vec3> * _normals;
		std::vector<glm::vec3> * _texCoords;

	};
}

#endif
