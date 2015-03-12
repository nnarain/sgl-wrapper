
#pragma once

#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "SGL/Util/SGLExport.h"

#include "SGL/GL/ShaderProgram.h"
#include "SGL/GL/Mesh.h"
#include "SGL/Util/Camera.h"
#include "SGL/2D/Sprite.h"

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
		NO_COPY(SpriteBatch);

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

	public:
		/* SpriteBatch Public Constructor and Destructor */

		SpriteBatch(void);
		~SpriteBatch(void);

	public:
		/* Public Functions */

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
		/* Private Members */

		//! The shader to draw with
		ShaderProgram* _shader;

		//!
		std::vector<Glyph>* _glyphs;
		//! 
		std::vector<Glyph*>* _glyphPointers;

		//! Mesh that the batches are bound to 
		Mesh _mesh;

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
