
#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <glm/glm.hpp>

#include <vector>
#include <map>

#include <SGL/Util/SGLExport.h>

#include <SGL/Util/ObjModel.h>

#include <SGL/Math/Vector2.h>
#include <SGL/Math/Vector3.h>

namespace sgl
{
	SGLCLASS ObjLoader
	{
	public:

		ObjLoader();
		~ObjLoader();

		void load(ObjModel &model, const std::string &filename);

	private:

		//!
		struct Face
		{
			int vertices[3];
			int normal[3];
			int texCoord[3];
		};

		struct MeshData
		{
			std::vector<Face> faces;
		};

		std::vector<Vector3> * _positions;
		std::vector<Vector3> * _normals;
		std::vector<Vector2> * _texCoords;

		std::map<std::string, MeshData> * _meshes;

		void parse(const std::string &filename);
		void bindToMesh(ObjModel &model);

		void createVertexFromTokens(Vector3 &v, std::vector<std::string> &tokens);
		void createUVFromTokens(Vector2 &uv, std::vector<std::string> &tokens);
		void createFaceFromTokens(Face& face, std::vector<std::string> &tokens);

		void tokenize(std::vector<std::string>& v, std::string &s, const std::string &delimiter);

	};
}

#endif
