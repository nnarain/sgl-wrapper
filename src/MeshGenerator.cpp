
#include "SGL/MeshGenerator.h"

#include <vector>

float g_CubeMeshData[] = {
	1.f, -1.f, 1.f, 0.5773f, -0.5773f, 0.5773f,
	-1.f, -1.f, 1.f, -0.5773f, -0.5773f, 0.5773f,
	-1.f, -1.f, -1.f, -0.5773f, -0.5773f, -0.5773f,
	-1.f, 1.f, -1.f, -0.5773f, 0.5773f, -0.5773f,
	-1.f, 1.f, 1.f, -0.5773f, 0.5773f, 0.5773f,
	0.999999f, 1.f, 1.f, 0.5773f, 0.5773f, 0.5773f,
	1.f, -1.f, -1.f, 0.5773f, -0.5773f, -0.5773f,
	1.f, 1.f, -0.999999f, 0.5773f, 0.5773f, -0.5773f,
	0.999999f, 1.f, 1.f, 0.5773f, 0.5773f, 0.5773f,
	1.f, -1.f, 1.f, 0.5773f, -0.5773f, 0.5773f,
	0.999999f, 1.f, 1.f, 0.5773f, 0.5773f, 0.5773f,
	-1.f, 1.f, 1.f, -0.5773f, 0.5773f, 0.5773f,
	-1.f, 1.f, 1.f, -0.5773f, 0.5773f, 0.5773f,
	-1.f, 1.f, -1.f, -0.5773f, 0.5773f, -0.5773f,
	-1.f, -1.f, -1.f, -0.5773f, -0.5773f, -0.5773f,
	1.f, -1.f, -1.f, 0.5773f, -0.5773f, -0.5773f,
	-1.f, -1.f, -1.f, -0.5773f, -0.5773f, -0.5773f,
	-1.f, 1.f, -1.f, -0.5773f, 0.5773f, -0.5773f,
	1.f, -1.f, -1.f, 0.5773f, -0.5773f, -0.5773f,
	1.f, -1.f, 1.f, 0.5773f, -0.5773f, 0.5773f,
	-1.f, -1.f, -1.f, -0.5773f, -0.5773f, -0.5773f,
	1.f, 1.f, -0.999999f, 0.5773f, 0.5773f, -0.5773f,
	-1.f, 1.f, -1.f, -0.5773f, 0.5773f, -0.5773f,
	0.999999f, 1.f, 1.f, 0.5773f, 0.5773f, 0.5773f,
	1.f, -1.f, 1.f, 0.5773f, -0.5773f, 0.5773f,
	1.f, -1.f, -1.f, 0.5773f, -0.5773f, -0.5773f,
	0.999999f, 1.f, 1.f, 0.5773f, 0.5773f, 0.5773f,
	-1.f, -1.f, 1.f, -0.5773f, -0.5773f, 0.5773f,
	1.f, -1.f, 1.f, 0.5773f, -0.5773f, 0.5773f,
	-1.f, 1.f, 1.f, -0.5773f, 0.5773f, 0.5773f,
	-1.f, -1.f, 1.f, -0.5773f, -0.5773f, 0.5773f,
	-1.f, 1.f, 1.f, -0.5773f, 0.5773f, 0.5773f,
	-1.f, -1.f, -1.f, -0.5773f, -0.5773f, -0.5773f,
	1.f, 1.f, -0.999999f, 0.5773f, 0.5773f, -0.5773f,
	1.f, -1.f, -1.f, 0.5773f, -0.5773f, -0.5773f,
	-1.f, 1.f, -1.f, -0.5773f, 0.5773f, -0.5773f,
};

SGLVOIDFUNC sgl::generateCubeMesh(sgl::Mesh* mesh, float scale)
{
	mesh->setDrawCount(36);
	mesh->create(g_CubeMeshData, sizeof(g_CubeMeshData), 6 * sizeof(float));
}

SGLVOIDFUNC sgl::generateWireframe(sgl::Mesh* mesh, void* buffer, int size, int stride)
{
	// iterating over bytes
	char* byteBuffer = (char*)buffer;
	int numTriangles = (int)((size / stride) / 3.0f);
	int i;

	std::vector<Line> lines;

	// iterate over bytes
	for (i = 0; i < numTriangles; i++)
	{
		// get the position vertices from the buffer
		glm::vec3 v1 = *(glm::vec3*)byteBuffer;
		byteBuffer += stride;
		
		glm::vec3 v2 = *(glm::vec3*)byteBuffer;
		byteBuffer += stride;

		glm::vec3 v3 = *(glm::vec3*)byteBuffer;
		byteBuffer += stride;

		// Create the line structure
		Line l1(v1, v2);
		Line l2(v2, v3);
		Line l3(v3, v1);

		lines.push_back(l1);
		lines.push_back(l2);
		lines.push_back(l3);
	}

	mesh->setDrawCount(lines.size() * 2);
	mesh->create(&lines[0], lines.size() * sizeof(Line), sizeof(glm::vec3));
}

SGLVOIDFUNC sgl::generateCubeWireframe(sgl::Mesh* mesh)
{
	generateWireframe(mesh, g_CubeMeshData, sizeof(g_CubeMeshData), 6 * sizeof(float));
}
