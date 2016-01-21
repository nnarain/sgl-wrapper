
#include "SGL/Util/DebugRenderer.h"
#include "SGL/Util/GLSL/GLSL_Position_Color.h"

using namespace sgl;

DebugRenderer::DebugRenderer() : _mesh(Mesh::Type::LINES, Buffer::Usage::STATIC_DRAW)
{
	_builder = new MeshBuilder<DebugVertex>();
}

void DebugRenderer::init()
{
	_shader.load(ShaderProgram::Type::VERTEX, GLSL_POSITION_COLOR_VERT);
	_shader.load(ShaderProgram::Type::FRAGMENT, GLSL_POSITION_COLOR_FRAG);
	_shader.addAttribute("vPosition");
	_shader.addAttribute("vColor");
	_shader.link();

	_mesh.addAttribute(VertexAttribute(0, 3));
	_mesh.addAttribute(VertexAttribute(1, 3));

	_mesh.create(sizeof(DebugVertex));
}

void DebugRenderer::begin()
{
	_builder->begin(&_mesh);
}

void DebugRenderer::add(Frustum& frustum)
{
	// get the frustum vertices
	Vector3f& lbn = frustum.getPoint(Frustum::PointId::LBN);
	Vector3f& ltn = frustum.getPoint(Frustum::PointId::LTN);
	Vector3f& rbn = frustum.getPoint(Frustum::PointId::RBN);
	Vector3f& rtn = frustum.getPoint(Frustum::PointId::RTN);

	Vector3f& lbf = frustum.getPoint(Frustum::PointId::LBF);
	Vector3f& ltf = frustum.getPoint(Frustum::PointId::LTF);
	Vector3f& rbf = frustum.getPoint(Frustum::PointId::RBF);
	Vector3f& rtf = frustum.getPoint(Frustum::PointId::RTF);

	// color
	sgl::Vector3f farColor(0, 1, 0);
	sgl::Vector3f nearColor(1, 0, 0);

	// near plane
	_builder->addLineQuad(DebugVertex(ltn, nearColor), DebugVertex(rtn, nearColor), DebugVertex(lbn, nearColor), DebugVertex(rbn, nearColor));
	// far plane
	_builder->addLineQuad(DebugVertex(ltf, farColor), DebugVertex(rtf, farColor), DebugVertex(lbf, farColor), DebugVertex(rbf, farColor));

	// top plane
	_builder->addLineQuad(DebugVertex(ltf, farColor), DebugVertex(rtf, farColor), DebugVertex(ltn, nearColor), DebugVertex(rtn, nearColor));
	// bottom plane
	_builder->addLineQuad(DebugVertex(lbf, farColor), DebugVertex(rbf, farColor), DebugVertex(lbn, nearColor), DebugVertex(rbn, nearColor));
}

void DebugRenderer::add(AABB& aabb)
{
	Vector3f lbn = aabb.center + Vector3f(-aabb.dim.x, -aabb.dim.y, -aabb.dim.z);
	Vector3f ltn = aabb.center + Vector3f(-aabb.dim.x, aabb.dim.y, -aabb.dim.z);
	Vector3f rbn = aabb.center + Vector3f(aabb.dim.x, -aabb.dim.y, -aabb.dim.z);
	Vector3f rtn = aabb.center + Vector3f(aabb.dim.x, aabb.dim.y, -aabb.dim.z);

	Vector3f lbf = aabb.center + Vector3f(-aabb.dim.x, -aabb.dim.y, aabb.dim.z);
	Vector3f ltf = aabb.center + Vector3f(-aabb.dim.x, aabb.dim.y, aabb.dim.z);
	Vector3f rbf = aabb.center + Vector3f(aabb.dim.x, -aabb.dim.y, aabb.dim.z);
	Vector3f rtf = aabb.center + Vector3f(aabb.dim.x, aabb.dim.y, aabb.dim.z);

	// near plane
	_builder->addLineQuad(DebugVertex(ltn), DebugVertex(rtn), DebugVertex(lbn), DebugVertex(rbn));
	// far plane
	_builder->addLineQuad(DebugVertex(ltf), DebugVertex(rtf), DebugVertex(lbf), DebugVertex(rbf));

	// top plane
	_builder->addLineQuad(DebugVertex(ltf), DebugVertex(rtf), DebugVertex(ltn), DebugVertex(rtn));
	// bottom plane
	_builder->addLineQuad(DebugVertex(lbf), DebugVertex(rbf), DebugVertex(lbn), DebugVertex(rbn));
}

void DebugRenderer::addLine(DebugVertex& v1, DebugVertex& v2)
{
	_builder->addLine(v1, v2);
}

void DebugRenderer::end()
{
	_builder->end();
}

void DebugRenderer::render(Matrix4& VP)
{
	_shader.begin();
	{
		_shader["VP"].set(VP);

		_mesh.bind();
		_mesh.draw();
		_mesh.unbind();
	}
	_shader.end();
}

DebugRenderer::~DebugRenderer()
{
	delete _builder;
}

