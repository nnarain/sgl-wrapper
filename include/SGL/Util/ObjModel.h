
#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <SGL/Util/SGLExport.h>
#include <SGL/GL/Mesh.h>

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
		void draw();
		void unbind();

		void addMeshData(const std::string &name, int offset, int vertexCount);

		void setMeshData(const std::string &name);
		void setMeshData(int idx);

		Mesh& getMesh();

	private:
		//! mesh containing render data for the obj model
		Mesh _mesh;

		//! number of vertices in mesh
		int _vertexCount;

		//! 
		std::map<std::string, MeshData> * _meshData;
		std::vector<std::string> * _meshDataKeys;
	};
}

#endif