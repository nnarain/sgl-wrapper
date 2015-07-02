
/**
	@author Natesh Narain
*/

#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include "SGL/Util/SGLExport.h"

#include "SGL/2D/SpriteBatch.h"
#include "SGL/GL/Texture.h"

#include "SGL/Math/Vector2.h"

#include <vector>

namespace sgl
{
	/**
		2D Font
	*/
	SGLCLASS BitmapFont
	{
	public:
		BitmapFont(void);
		~BitmapFont(void);

		/**
			Initialize the font

			@param filename
				bitmap font file

			@param cols
				Number of columns

			@param rows
				Number of rows

			@param flip
				Load the regions flipped
		*/
		void init(const char *filename, unsigned int cols, unsigned int rows, bool flip);

		/**
			@return the region corresponding to the character
		*/
		Texture::TextureRegion& getCharRegion(char c);

		/**
			@return the texture of this font
		*/
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

		// list of regions
		std::vector<Texture::TextureRegion> * _regions;

		void initTexture(const char *filename);
	};
}

#endif
