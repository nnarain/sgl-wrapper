
#include "SGL/2D/BitmapFont.h"

using namespace sgl;

BitmapFont::BitmapFont(void) : BitmapFont(NULL)
{

}

BitmapFont::BitmapFont(Texture* texture) :
	_texture(texture),
	_dimension(40, 40),
	_regions(new std::vector<Texture::TextureRegion>()),
	_cells(new std::vector<Cell>())
{

}

void BitmapFont::draw(SpriteBatch& batch)
{
	draw(batch, false, false);
}

void BitmapFont::draw(SpriteBatch& batch, bool flipH, bool flipV)
{
	std::vector<Cell>::iterator iter;
	for (iter = _cells->begin(); iter != _cells->end(); ++iter)
	{
		batch.draw((*iter).quad, (*iter).region, _texture, flipH, flipV);
	}
}

void BitmapFont::puts(const char *str)
{
	// clear any existing cells
	_cells->clear();

	//
	float x = _position.x;
	float y = _position.y;

	while (*str)
	{
		char c = *str++;
		char idx = c - 32;

		Quad quad;
		util::makeQuad(quad, x, y, _dimension.x, _dimension.y);

		x += _dimension.x;

		_cells->emplace_back(quad, _regions->at(idx));
	}
}

void BitmapFont::setTexture(Texture* texture, unsigned int cols, unsigned int rows, bool flip)
{
	_texture = texture;
	_cols    = cols;
	_rows    = rows;

	_dimension.x = (float)(texture->getWidth() / _cols);
	_dimension.y = (float)(texture->getHeight() / _rows);

	// calculate the texture regions for each cell
	if (flip)
	{
		unsigned int i, j;
		for (i = rows; i >= 1; --i)
		{
			for (j = 0; j < cols; ++j)
			{
				Texture::TextureRegion region = texture->region((j * _dimension.x), (i * _dimension.y) - _dimension.y, _dimension.x, _dimension.y);
				_regions->push_back(region);
			}
		}
	}
	else
	{
		unsigned int i, j;
		for (i = 0; i < rows; ++i)
		{
			for (j = 0; j < cols; ++j)
			{
				Texture::TextureRegion region = texture->region((j * _dimension.x), (i * _dimension.y), _dimension.x, _dimension.y);
				_regions->push_back(region);
			}
		}
	}
}

void BitmapFont::setPosition(Vector2& pos)
{
	setPosition(pos.x, pos.y);
}

void BitmapFont::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}

BitmapFont::~BitmapFont(void)
{
	delete _regions;
	delete _cells;
}
