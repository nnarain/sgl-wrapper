
#include "SGL/2D/Text.h"

using namespace sgl;

Text::Text(void) :
	_position(0,0),
	_dimension(40,40),
	_cells(new std::vector<Cell>())
{
}

void Text::draw(SpriteBatch& batch, bool flipH, bool flipV)
{
	std::vector<Cell>::iterator iter;
	for (iter = _cells->begin(); iter != _cells->end(); ++iter)
	{
		batch.draw((*iter).quad, (*iter).region, _font->getTexture(), flipH, flipV);
	}
}

void Text::draw(SpriteBatch& batch)
{
	draw(batch, false, false);
}

void Text::puts(const char *str)
{
	// clear any existing cells
	_cells->clear();

	//
	float x = _position.x;
	float y = _position.y;

	while (*str)
	{
		char c = *str++;

		Quad quad;
		util::makeQuad(quad, x, y, _dimension.x, _dimension.y);

		x += _dimension.x;

		_cells->emplace_back(quad, _font->getCharRegion(c));
	}
}

void Text::setFont(BitmapFont* font)
{
	_font = font;
}

BitmapFont *Text::getFont(void) const
{
	return _font;
}

void Text::setPosition(const Vector2& pos)
{
	setPosition(pos.x, pos.y);
}

void Text::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}

Vector2& Text::getPosition(void)
{
	return _position;
}

Text::~Text(void)
{
	delete _cells;
}