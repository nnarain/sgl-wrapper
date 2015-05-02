
#ifndef TEXT_H
#define TEXT_H

#include "SGL/Util/SGLExport.h"

#include "SGL/2D/SpriteBatch.h"
#include "SGL/2D/BitmapFont.h"

#include "SGL/Type/Geometry.h"
#include "SGL/GL/Texture.h"

#include "SGL/Math/Vector2.h"

#include <vector>

namespace sgl
{
	SGLCLASS Text
	{
	public: 
		Text(void);
		~Text(void);

		void draw(SpriteBatch& batch);
		void draw(SpriteBatch& batch, bool flipH, bool flipV);

		void puts(const char *str);

		void setFont(BitmapFont*);
		BitmapFont *getFont(void) const;

		void setPosition(const Vector2&);
		void setPosition(float x, float y);

		Vector2& getPosition(void);

	private:
		/* Types */

		//! Font Cell
		struct Cell
		{
			Quad quad;
			Texture::TextureRegion region;

			Cell(Quad& q, Texture::TextureRegion& r)
			{
				quad = q;
				region = r;
			}
		};

		BitmapFont* _font;

		Vector2 _position;
		Vector2 _dimension;

		std::vector<Cell>* _cells;

	};
}

#endif
