
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
		class Glyph
		{
		public:
			Glyph(void);
			Glyph(Quad& quad, Texture::TextureRegion& region, Texture*);

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



		/* Draw functions */

		/**
			Add the given sprite to the batch to be rendered
		*/
		void draw(Sprite& sprite);

		/**
			Add a sprite, with option to flip on horizontal and vertical axis
		*/
		void draw(Sprite& sprite, bool flipH, bool flipV);

		/**
			Base draw
		*/
		void draw(Quad& quad, Texture::TextureRegion& region, Texture* texture);



		/**
			render the batches and tidy up
		*/
		void end();

	private:

		//! The shader to draw with
		ShaderProgram* _shader;
		//! 
		std::vector<Glyph*>* _glyphPointers;
		std::vector<Glyph>* _glyphs;

		//! Mesh that the batches are bound to 
		Mesh* _mesh;

		//! batch begin flag
		bool _isActive;

		/**
			Render the given batch with its given texture
		*/
		void render(Texture* texture, std::vector<Vertex> *batch);
		
		/**
			batch and render
		*/
		void renderBatch();

		/**
			Flip a texture region horizontally or vertically
		*/
		void flip(Texture::TextureRegion& region, bool horizontal, bool vertical);

		/**
			Sort Glyphs
		*/
		static bool sortGlyphs(Glyph* glyph1, Glyph* glyph2);
	};
};

#endif
