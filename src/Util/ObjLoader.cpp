
#include "SGL/Util/ObjLoader.h"

#include <SGL/Util/Exception.h>

#include <fstream>

using namespace sgl;

ObjLoader::ObjLoader() : 
	_positions(new std::vector<glm::vec3>),
	_normals(new std::vector<glm::vec3>),
	_texCoords(new std::vector<glm::vec2>),
	_faces(new std::vector<Face>)
{
}

void ObjLoader::load(ObjModel &model, const std::string &filename)
{
	parse(model, filename);
	bindToMesh(model.getMesh());
}

void ObjLoader::bindToMesh(Mesh &mesh)
{
	const int vertSize = _positions->size();
	const int normSize = _normals->size();
	const int uvSize   = _texCoords->size();

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

	std::vector<Face>::iterator iter;
	for (iter = _faces->begin(); iter != _faces->end(); ++iter)
	{
		Face face = (*iter);

		int i;
		for (i = 0; i < 3; ++i)
		{
			int vIdx = face.vertices[i] - 1;
			int nIdx = face.normal[i] - 1;
			int tIdx = face.texCoord[i] - 1;

			if (vertSize > 0)
			{
				buffer.push_back(_positions->at(vIdx).x);
				buffer.push_back(_positions->at(vIdx).y);
				buffer.push_back(_positions->at(vIdx).z);
			}

			if (normSize > 0)
			{
				buffer.push_back(_normals->at(nIdx).x);
				buffer.push_back(_normals->at(nIdx).y);
				buffer.push_back(_normals->at(nIdx).z);
			}

			if (uvSize > 0)
			{
				buffer.push_back(_texCoords->at(tIdx).x);
				buffer.push_back(_texCoords->at(tIdx).y);
			}
		}
	}
	
	// faces times 3 vertices per triangle
	int drawCount = _faces->size() * 3;

	// bind vertex data to mesh
	Buffer& vbo = mesh.getVBO();
	vbo.bind();
	vbo.setData(&buffer[0], buffer.size() * sizeof(float));
	vbo.unbind();

	mesh.setDrawCount(drawCount);
	
	mesh.create(stride * sizeof(float));
}

void ObjLoader::parse(ObjModel &model, const std::string &filename)
{
	std::ifstream file(filename);

	if (!file.good())
		throw Exception("could not open file: " + filename);

	//
	std::string currentMesh;
	int offset = 0;
	int vertexPerMesh = 0;

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
			// switching to a new mesh so add the current one to the model
			if (vertexPerMesh != 0)
			{
				// add the current mesh data into the model
				model.addMeshData(currentMesh, offset, vertexPerMesh);

				// increment the offset
				offset += vertexPerMesh;
				// reset vertex count
				vertexPerMesh = 0;
			}

			// set to the new mesh
			currentMesh = tokens[1];
		}
		// new vertex
		else if (head == "v")
		{
			glm::vec3 v;
			createVertexFromTokens(v, tokens);

			_positions->push_back(v);
			vertexPerMesh++;
		}
		// new normal
		else if (head == "vn")
		{
			glm::vec3 n;
			createVertexFromTokens(n, tokens);

			_normals->push_back(n);
		}
		// new teexcoord
		else if (head == "vt")
		{
			glm::vec2 uv;
			createUVFromTokens(uv, tokens);

			_texCoords->push_back(uv);
		}
		// new face
		else if (head == "f")
		{
			Face f;
			createFaceFromTokens(f, tokens);

			_faces->push_back(f);
		}
	}
}

void ObjLoader::createVertexFromTokens(glm::vec3 &v, std::vector<std::string> &tokens)
{
	v.x = (float)(atof(tokens[1].c_str()));
	v.y = (float)(atof(tokens[2].c_str()));
	v.z = (float)(atof(tokens[3].c_str()));
}

void ObjLoader::createUVFromTokens(glm::vec2 &uv, std::vector<std::string> &tokens)
{
	uv.s = (float)atof(tokens[1].c_str());
	uv.t = (float)atof(tokens[2].c_str());
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

ObjLoader::~ObjLoader()
{
	delete _positions;
	delete _normals;
	delete _texCoords;
	delete _faces;
}
