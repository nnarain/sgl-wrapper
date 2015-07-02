
#include "SGL/2D/Text.h"

#include <cstdarg>

using namespace sgl;

Text::Text(void) :
	_position(0,0),
	_offset(0,0),
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

void Text::append(const char *str)
{
	while (*str)
	{
		char c = *str++;

		if (c == '\n')
		{
			_offset.x = _position.x;
			_offset.y -= _dimension.y;
		}
		else if (c == '\r')
		{
		}
		else
		{
			Rect quad;
			util::makeQuad(quad, _offset.x, _offset.y, _dimension.x, _dimension.y);

			_offset.x += _dimension.x;

			_cells->emplace_back(quad, _font->getCharRegion(c));
		}
	}
}

void Text::format(const char *fmt, ...)
{
	va_list args;
	char buff[50];

	va_start(args, fmt);
	vsnprintf_s(buff, 50, fmt, args);
	va_end(args);

	append(buff);
}

void Text::clear(void)
{
	_cells->clear();
	setPosition(_position);
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
	_offset.x = x;
	_offset.y = y;
}

Vector2& Text::getPosition(void)
{
	return _position;
}

void Text::setDimensions(const Vector2& dim)
{
	setDimensions(dim.x, dim.y);
}

void Text::setDimensions(float w, float h)
{
	_dimension.x = w;
	_dimension.y = h;
}

Vector2& Text::getDimensions(void)
{
	return _dimension;
}

Text::~Text(void)
{
	delete _cells;
}