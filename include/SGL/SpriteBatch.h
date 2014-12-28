
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
	/**
		Use this class to render sprites.

		This class will origanize sprites in 'batches'
		sorted by texture to optimize texture binds and draw calls

		Shader Requirements:

			The SpriteBatch provides and 2D position and 2D texture coordinate vertex attributes.	
			- Bind the position to input 0
			- Bind the texture coordinate to input 1
			- Provide uniform sampler2D called texture
	*/
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

		/* SpriteBatch members */

		SpriteBatch(void);
		~SpriteBatch(void);

		/**
			Get ready to draw sprites.

			@param shader
				the shader to use to draw
		*/
		void begin(ShaderProgram* shader);

		/**
			Add the given sprite to the batch to be rendered
		*/
		void draw(Sprite& sprite);

		/**
			render the batches and tidy up
		*/
		void end();

	private:

		//! The shader to draw with
		ShaderProgram* _shader;
		//! 
		std::vector<Glyph*> _glyphBuffer;

		//! Mesh that the batches are bound to 
		Mesh* _mesh;

		/**
			Render the given batch with its given texture
		*/
		void render(Texture* texture, std::vector<Vertex> *batch);
		
		/**
			batch and render
		*/
		void renderBatch();
	};
};

#endif
