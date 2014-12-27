
#pragma once

#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "SGLExport.h"

#include "ShaderProgram.h"
#include "Camera.h"
#include "Sprite.h"

#include <vector>

namespace sgl
{
	SGLCLASS SpriteBatch
	{
	public:

		/* Types */

		//! Vertex. Position and texture coordinates
		struct Vertex
		{
			glm::vec2 pos;
			glm::vec2 texCoord;
		};

		//! Intermediate structure to store vertex data before the batching stage
		struct Glyph
		{
			Texture* texture;

			Vertex v1;
			Vertex v2;
			Vertex v3;
			Vertex v4;
		};

		SpriteBatch();
		~SpriteBatch();

		void begin(ShaderProgram* shader);
		void draw(Sprite& sprite);
		void end();

	private:

		ShaderProgram* _shader;
		std::vector<Glyph*> _glyphBuffer;

		Mesh* _mesh;

		void render(Texture* texture, std::vector<Vertex> *batch);
		void renderBatch();
	};
};

#endif
