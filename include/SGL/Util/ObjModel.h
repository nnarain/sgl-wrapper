
#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <SGL/Util/SGLExport.h>
#include <SGL/GL/Mesh.h>
#include <SGL/GL/Texture.h>

#include <map>

namespace sgl
{
	SGLCLASS ObjModel
	{
	public:
		/* Types */

		//! Mesh Data
		struct MeshData
		{
			int offset;
			int drawCount;
		};

		ObjModel();
		~ObjModel();

		void bind();
		void bind(Texture::Unit unit);

		void draw();
		void unbind();

		void addMeshData(const std::string &name, int offset, int vertexCount);

		void setMeshData(const std::string &name);
		void setMeshData(int idx);

		Mesh& getMesh();

		Texture& getTexture();

	private:
		//! mesh containing render data for the obj model
		Mesh _mesh;

		//! optional model texture
		Texture _texture;

		//! number of vertices in mesh
		int _vertexCount;

		//! 
		std::map<std::string, MeshData> * _meshData;
		std::vector<std::string> * _meshDataKeys;
	};
}

#endif
