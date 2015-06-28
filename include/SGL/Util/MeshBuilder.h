
#ifndef MESHBUILDER_H
#define MESHBUILDER_H

#include "SGL/GL/Mesh.h"

#include <vector>
#include <cassert>

namespace sgl
{
	template<typename Vertex>
	class MeshBuilder
	{
	public:

		void begin(Mesh* mesh)
		{
			assert(mesh != NULL && "Mesh an not be NULL");
			
			_mesh = mesh;
		}

		void end()
		{
			int size = _vertexBuffer.size();

			//
			_mesh->setDrawCount(size);

			//
			Buffer& vbo = _mesh->getVBO();
			vbo.bind();
			
			if (_vertexBuffer.size() > 0)
			{
				vbo.setData(&_vertexBuffer[0], size * sizeof(Vertex));
			}
			else
			{
				vbo.setData(0, 0);
			}

			vbo.unbind();

			//
			_mesh = NULL;
			_vertexBuffer.clear();
		}

		/* Added Vertex Functions */

		void addVertex(Vertex& v)
		{
			assert(_mesh != NULL && "MeshBuilder has not been started");

			_vertexBuffer.push_back(v);
		}

		void addLine(Vertex& v1, Vertex& v2)
		{
			assert(_mesh != NULL && "MeshBuilder has not been started");

			_vertexBuffer.push_back(v1);
			_vertexBuffer.push_back(v2);
		}

		void addTriangle(Vertex& v1, Vertex& v2, Vertex& v3)
		{
			assert(_mesh != NULL && "MeshBuilder has not been started");

			_vertexBuffer.push_back(v1);
			_vertexBuffer.push_back(v2);
			_vertexBuffer.push_back(v3);
		}

		/**
			Adds a Quad to the mesh.

			Vertices are ordered left to right, top to bottom so:

			v1 ------- v2
			|           |
			|           |
			|           |
			|           |
			v3 ------- v4

			The first triangle is made with v1, v2 and v3
			The second triangle is made with v2, v3 and v4
		*/
		void addQuad(Vertex& v1, Vertex& v2, Vertex& v3, Vertex& v4)
		{
			assert(_mesh != NULL && "MeshBuilder has not been started");

			addTriangle(v1, v2, v3);
			addTriangle(v2, v3, v4);
		}

		/**
			Add a box made of lines

			Vertices are ordered left to right, top to bottom so:

			v1 ------- v2
			|           |
			|           |
			|           |
			|           |
			v3 ------- v4
		*/
		void addLineQuad(Vertex& v1, Vertex& v2, Vertex& v3, Vertex& v4)
		{
			addLine(v1, v2);
			addLine(v3, v4);
			addLine(v1, v3);
			addLine(v2, v4);
		}

	private:

		Mesh* _mesh;
		std::vector<Vertex> _vertexBuffer;

	};
}

#endif
