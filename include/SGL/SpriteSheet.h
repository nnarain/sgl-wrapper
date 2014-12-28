
#pragma once

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "SGLExport.h"

#include "Sprite.h"

#include <vector>

namespace sgl
{
	/**
		Divides a region of the given texture into cells for easy access
	*/
	SGLCLASS SpriteSheet
	{
	public:
		/**
			Create a sheet with (x, y) pixel coordinate. width and height in pixels.
			number of rows and columns. and the texture it uses
		*/
		SpriteSheet(float x, float y, float w, float h, int rows, int cols, Texture* texture);
		~SpriteSheet();

		/**
			Initialize the sprite sheet and set the width and height
		*/
		void init(float w, float h);

		/**
			@return the sprite
		*/
		Sprite& getSprite();

		/**
			@return the sprite with the specified texture region
		*/
		Sprite& getSprite(int idx);

		/**
			Get the number of sprites
		*/
		int getNumSprites();

	private:
		//! The texture that the sheet maps to
		Texture* _texture;
		
		//!
		Sprite* _sprite;
		//! Hold the texture corrdinates of each cell
		std::vector<Texture::TextureRegion> _regions;

		//! bottom left x coord of the sheets sections in the texture
		float _x;
		//! bottom left y coord of the sheets sections in the texture
		float _y;

		//! sheet width
		float _width;
		//! shhet height
		float _height;
		
		//! number of rows in the sheet
		int _rows;
		//! number of columns in the sheet
		int _cols;
	};
};

#endif
