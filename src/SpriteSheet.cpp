
#include "SGL/SpriteSheet.h"

using namespace sgl;

SpriteSheet::SpriteSheet(float x, float y, float w, float h, int rows, int cols, Texture* texture)
{
	_texture = texture;
	//_region = _texture->region(x, y, w, h);

	_x = x;
	_y = y;

	_width = w;
	_height = h;

	_rows = rows;
	_cols = cols;

	_sprite = new Sprite(0, 0, 0, 0, texture);
	_regions = new std::vector<Texture::TextureRegion>();
}

void SpriteSheet::init(float w, float h)
{
	_sprite->setDimensions(w, h);

	// calculate the width and height of a cell of the sheet
	float cellWidth = _width / _cols;
	float cellHeight = _height / _rows;

	// calculate the width, height and position of each sprite in the sheet
	int i, j;
	for (i = 0; i < _cols; ++i)
	{
		for (j = 0; j < _rows; ++j)
		{
			_regions->push_back(
				// position the cell i widths over from the sheet offset in the texture
				// position the cell j heights over from the sheet offset in the texture
				_texture->region(_x + (cellWidth * i), _y + (cellHeight * j), cellWidth, cellHeight)
			);
		}
	}
}

Sprite& SpriteSheet::getSprite()
{
	return *_sprite;
}

Sprite& SpriteSheet::getSprite(int idx)
{
	_sprite->setTextureRegion((*_regions)[idx]);
	return *_sprite;
}

int SpriteSheet::getNumSprites()
{
	return _rows * _cols;
}

SpriteSheet::~SpriteSheet()
{
	delete _regions;
}