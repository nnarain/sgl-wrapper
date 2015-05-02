
#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include "SGL/Util/SGLExport.h"

#include "SGL/2D/SpriteBatch.h"
#include "SGL/GL/Texture.h"
#include "SGL/Type/Geometry.h"

#include "SGL/Math/Vector2.h"

#include <vector>

namespace sgl
{
	/**
		Render 2D Font
	*/
	SGLCLASS BitmapFont
	{
	public:
		BitmapFont(void);
		BitmapFont(Texture*);
		~BitmapFont(void);

		void draw(SpriteBatch&, bool flipH, bool flipV);
		void draw(SpriteBatch&);

		void puts(const char *str);

		void setTexture(Texture*, unsigned int cols, unsigned int rows, bool flip);

		void setPosition(Vector2& pos);
		void setPosition(float x, float y);

	private:
		/* Types */

		//! Font Cell
		struct Cell
		{
			Quad quad;
			Texture::TextureRegion region;

			Cell(Quad& q, Texture::TextureRegion& r)
			{
				quad   = q;
				region = r;
			}
		};

		// the font texture
		Texture* _texture;

		// text position (pixels)
		Vector2 _position;
		// cell dimension (pixels)
		Vector2 _dimension;

		// number of columsn in the font
		unsigned int _cols;
		// number of rows in the font
		unsigned int _rows;

		//
		std::vector<Cell> * _cells;

		//
		std::vector<Texture::TextureRegion> * _regions;
	};
}

#endif
