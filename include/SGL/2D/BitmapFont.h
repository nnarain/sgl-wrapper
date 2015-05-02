
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
		~BitmapFont(void);

		void init(const char *filename, unsigned int cols, unsigned int rows, bool flip);

		Texture::TextureRegion& getCharRegion(char c);

		Texture* getTexture(void);

	private:

		// the font texture
		Texture _texture;

		// cell dimension (pixels)
		Vector2 _dimension;

		// number of columsn in the font
		unsigned int _cols;
		// number of rows in the font
		unsigned int _rows;

		//
		std::vector<Texture::TextureRegion> * _regions;

		void initTexture(const char *filename);
	};
}

#endif
