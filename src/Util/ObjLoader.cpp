
#include "SGL/Util/ObjLoader.h"

#include <SGL/Util/Image.h>
#include <SGL/Util/Exception.h>

#include <fstream>

using namespace sgl;

ObjLoader::ObjLoader() : 
	_positions(new std::vector<Vector3>),
	_normals(new std::vector<Vector3>),
	_texCoords(new std::vector<Vector2>),
	_meshes(new std::map<std::string, MeshData>)
{
}

void ObjLoader::load(ObjModel &model, const char *modelpath)
{
	load(model, modelpath, NULL);
}

void ObjLoader::load(ObjModel &model, const char *modelpath, const char * texturepath)
{
	load(model, modelpath, texturepath, false);
}

void ObjLoader::load(ObjModel &model, const char *modelpath, const char * texturepath, bool invertUV)
{
	if (texturepath != NULL)
	{
		loadTexture(model.getTexture(), texturepath);
	}

	parse(modelpath);
	bindToMesh(model, invertUV);
}


void ObjLoader::bindToMesh(ObjModel &model, bool invertUV)
{
	const int vertSize = _positions->size();
	const int normSize = _normals->size();
	const int uvSize   = _texCoords->size();

	Mesh &mesh = model.getMesh();

	// calculate the vertex data stride
	int stride = 0;
	if (vertSize > 0)
	{ 
		mesh.addAttribute(VertexAttribute(0, 3));
		stride += 3;
	}
	if (normSize > 0)
	{
		mesh.addAttribute(VertexAttribute(1, 3));
		stride += 3;
	}
	if (uvSize > 0)
	{
		mesh.addAttribute(VertexAttribute(2, 2));
		stride += 2;
	}

	std::vector<float> buffer;
	int offset = 0;

	std::map<std::string, MeshData>::iterator meshIter;

	for (meshIter = _meshes->begin(); meshIter != _meshes->end(); ++meshIter)
	{
		const std::string &meshName = (*meshIter).first;
		MeshData &mesh = (*meshIter).second;
		std::vector<Face> &faces = mesh.faces;

		// set mesh data
		int drawCount = faces.size() * 3; // each face is a triangle (3 vertices)

		model.addMeshData(meshName, offset, drawCount);
		
		offset += drawCount;

		std::vector<Face>::iterator iter;
		for (iter = faces.begin(); iter != faces.end(); ++iter)
		{
			Face& face = (*iter);

			int i;
			for (i = 0; i < 3; ++i)
			{
				int vIdx = face.vertices[i] - 1;
				int nIdx = face.normal[i] - 1;
				int tIdx = face.texCoord[i] - 1;

				if (vertSize > 0)
				{
					Vector3& v = _positions->at(vIdx);
					buffer.push_back(v.x);
					buffer.push_back(v.y);
					buffer.push_back(v.z);
				}

				if (normSize > 0)
				{
					Vector3& n = _normals->at(nIdx);
					buffer.push_back(n.x);
					buffer.push_back(n.y);
					buffer.push_back(n.z);
				}

				if (uvSize > 0)
				{
					Vector2 &uv = _texCoords->at(tIdx);
					buffer.push_back(uv.x);
					buffer.push_back(invertUV ? 1.0f - uv.y : uv.y);
				}
			}
		}
	}
	
	// faces times 3 vertices per triangle
	int drawCount = offset;

	// bind vertex data to mesh
	Buffer& vbo = mesh.getVBO();
	vbo.bind();
	vbo.setData(&buffer[0], buffer.size() * sizeof(float));
	vbo.unbind();

	mesh.setDrawCount(drawCount);
	
	mesh.create(stride * sizeof(float));
}

void ObjLoader::parse(const char * filename)
{
	std::ifstream file(filename);

	if (!file.good())
		throw Exception("could not open file: " + std::string(filename));

	//
	std::string currentMesh = "";
	int offset = 0;
	int vertexPerMesh = 0;
	int numFaces = 0;
	bool newMesh = false;

	// read the file line by line
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<std::string> tokens;
		tokenize(tokens, line, " ");

		// get the first character representing the kind of data the line is
		const std::string &head = tokens[0];

		// new comment
		if (head == "#")
		{
			// skip
			continue;
		}

		// new mesh
		if (head == "o")
		{
			currentMesh = tokens[1];
			(*_meshes)[currentMesh] = MeshData();
		}
		// new vertex
		else if (head == "v")
		{
			Vector3 v;
			createVertexFromTokens(v, tokens);

			_positions->push_back(v);
		}
		// new normal
		else if (head == "vn")
		{
			Vector3 n;
			createVertexFromTokens(n, tokens);

			_normals->push_back(n);
		}
		// new teexcoord
		else if (head == "vt")
		{
			Vector2 uv;
			createUVFromTokens(uv, tokens);

			_texCoords->push_back(uv);
		}
		// new face
		else if (head == "f")
		{
			Face f;
			createFaceFromTokens(f, tokens);

			(*_meshes)[currentMesh].faces.push_back(f);
		}
	}
}

void ObjLoader::createVertexFromTokens(Vector3 &v, std::vector<std::string> &tokens)
{
	v.x = (float)(atof(tokens[1].c_str()));
	v.y = (float)(atof(tokens[2].c_str()));
	v.z = (float)(atof(tokens[3].c_str()));
}

void ObjLoader::createUVFromTokens(Vector2 &uv, std::vector<std::string> &tokens)
{
	uv.x = (float)atof(tokens[1].c_str());
	uv.y = (float)atof(tokens[2].c_str());
}

void ObjLoader::createFaceFromTokens(Face& f, std::vector<std::string> &tokens)
{
	const int size = tokens.size();
	int i;

	for (i = 1; i < size; i++){

		// tokens holding vertex, normal and texture indicies
		std::vector<std::string> vntTokens;
		tokenize(vntTokens, tokens[i], "/");

		f.vertices[i - 1] = atoi(vntTokens[0].c_str());
		f.normal  [i - 1] = atoi(vntTokens[2].c_str());
		f.texCoord[i - 1] = atoi(vntTokens[1].c_str());
	}
}

void ObjLoader::tokenize(std::vector<std::string>& tokens, std::string &s, const std::string &delimiter)
{
	// check that is still valid
	while (s.find(delimiter, 0) != std::string::npos){
		// get pos of next delimiter
		size_t pos = s.find(delimiter, 0);
		// create a token
		std::string token = s.substr(0, pos);
		// erase the current token 
		s.erase(0, pos + 1);
		// add the token to  vector
		tokens.push_back(token);
	}
	// push the last token
	tokens.push_back(s);
}

void ObjLoader::loadTexture(sgl::Texture& texture, const char * filename)
{
	texture.bind();

	Image::load(texture, filename);

	texture.parameter(Texture::ParamName::MAG_FILTER, Texture::Param::LINEAR);
	texture.parameter(Texture::ParamName::MIN_FILTER, Texture::Param::LINEAR);

	texture.unbind();
}

ObjLoader::~ObjLoader()
{
	delete _positions;
	delete _normals;
	delete _texCoords;
	delete _meshes;
}
