
#include "SGL/2D/BitmapFont.h"
#include "SGL/Util/Image.h"

using namespace sgl;


BitmapFont::BitmapFont(void) :
	_texture(Texture::Target::TEXTURE2D),
	_regions(new std::vector<Texture::TextureRegion>())
{

}

void BitmapFont::init(const char *filename, unsigned int cols, unsigned int rows, bool flip)
{
	// load the texture
	initTexture(filename);

	_cols    = cols;
	_rows    = rows;

	_dimension.x = (float)(_texture.getWidth() / _cols);
	_dimension.y = (float)(_texture.getHeight() / _rows);

	// calculate the texture regions for each cell
	if (flip)
	{
		unsigned int i, j;
		for (i = rows; i >= 1; --i)
		{
			for (j = 0; j < cols; ++j)
			{
				Texture::TextureRegion region = _texture.region((j * _dimension.x), (i * _dimension.y) - _dimension.y, _dimension.x, _dimension.y);
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
				Texture::TextureRegion region = _texture.region((j * _dimension.x), (i * _dimension.y), _dimension.x, _dimension.y);
				_regions->push_back(region);
			}
		}
	}
}

void BitmapFont::initTexture(const char *filename)
{
	_texture.bind();
	
	Image::load(_texture, filename);

	_texture.parameter(Texture::ParamName::MAG_FILTER, Texture::Param::LINEAR);
	_texture.parameter(Texture::ParamName::MIN_FILTER, Texture::Param::LINEAR);

	_texture.unbind();
}

Texture::TextureRegion& BitmapFont::getCharRegion(char c)
{
	// range of printable characters starts at 32
	int idx = c - 32;

	return _regions->at(idx);
}

Texture* BitmapFont::getTexture(void)
{
	return &_texture;
}

BitmapFont::~BitmapFont(void)
{
	delete _regions;
}
