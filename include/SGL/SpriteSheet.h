
#pragma once

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "SGLExport.h"

#include "Sprite.h"

#include <vector>

namespace sgl
{
	SGLCLASS SpriteSheet
	{
	public:
		SpriteSheet(float x, float y, float w, float h, int rows, int cols, Texture* texture);
		~SpriteSheet();

		void init(float w, float h);

		Sprite& getSprite();
		Sprite& getSprite(int idx);

		int getNumSprites();

	private:
		Texture* _texture;
		Texture::TextureRegion _region;
		
		Sprite* _sprite;
		std::vector<Texture::TextureRegion> _regions;

		float _x;
		float _y;

		float _width;
		float _height;
		
		int _rows;
		int _cols;
	};
};

#endif
