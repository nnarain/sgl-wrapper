
#include "SGL/SpriteSheet.h"

#include <algorithm>

using namespace sgl;

SpriteSheet::SpriteSheet(float x, float y, float w, float h, int rows, int cols, Texture* texture) :
	_texture(texture),
	_x(x),
	_y(y),
	_width(w),
	_height(h),
	_rows(rows),
	_cols(cols),
	_sprite(new Sprite(0,0,0,0, texture)),
	_regions(new std::vector<Texture::TextureRegion>)
{

}

SpriteSheet::SpriteSheet(const SpriteSheet& that) :
	SpriteSheet::SpriteSheet(that._x, that._y, that._width, that._height, that._rows, that._cols, that._texture)
{
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

void sgl::swap(SpriteSheet& first, SpriteSheet& second)
{
	using std::swap;

	swap(first._cols, second._cols);
	swap(first._height, second._height);
	swap(first._regions, second._regions);
	swap(first._rows, second._rows);
	swap(first._texture, second._texture);
	swap(first._sprite, second._sprite);
	swap(first._width, second._width);
	swap(first._x, second._x);
	swap(first._y, second._y);
}

SpriteSheet& SpriteSheet::operator=(SpriteSheet that)
{
	swap(*this, that);
	return *this;
}

SpriteSheet::~SpriteSheet()
{
	delete _sprite;
	delete _regions;
}