
#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H

#include "SGL/Util/SGLExport.h"

#include "SGL/GL/ShaderProgram.h"
#include "SGL/GL/Mesh.h"
#include "SGL/Util/MeshBuilder.h"

#include "SGL/Math/Matrix4.h"

#include "SGL/Math/Frustum.h"
#include "SGL/Math/AABB.h"

namespace sgl
{
	struct DebugVertex
	{
		DebugVertex(const Vector3f p) : DebugVertex(p, Vector3f(0,0,0))
		{
		}

		DebugVertex(const Vector3f& p, const Vector3f& c) : position(p), color(c)
		{
		}

		Vector3f position;
		Vector3f color;
	};

	SGLCLASS DebugRenderer
	{
	public:

		DebugRenderer();
		~DebugRenderer();

		void init();

		void render(Matrix4& VP);

		void begin();
		void end();

		void add(Frustum& frustum);
		void add(AABB& aabb);

		void addLine(DebugVertex& v1, DebugVertex& v2);


	private:

		ShaderProgram             _shader;
		Mesh                      _mesh;
		MeshBuilder<DebugVertex>* _builder;

	};
}

#endif
