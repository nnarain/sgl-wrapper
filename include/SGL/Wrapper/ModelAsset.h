
#ifndef MODELASSET_H
#define MODELASSET_H

#include <SGL/Wrapper/ShaderProgram.h>
#include <SGL/Wrapper/Texture.h>
#include <SGL/Wrapper/Mesh.h>

namespace sgl
{
	struct ModelAsset
	{
		ShaderProgram *shader;
		Texture       *texture;
		Mesh          *mesh;
	};
}

#endif
