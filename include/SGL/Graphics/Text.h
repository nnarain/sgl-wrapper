
/**
	@author Natesh Narain
*/

#ifndef TEXT_H
#define TEXT_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Graphics/SpriteBatch.h"
#include "SGL/Graphics/BitmapFont.h"
#include "SGL/Graphics/Color.h"

#include "SGL/GL/Texture.h"

#include "SGL/Math/Vector2.h"

#include <vector>
#include <sstream>

namespace sgl
{
	/**
		2D Text
	*/
	SGLCLASS Text
	{
	public: 
		Text(void);
		~Text(void);

		void draw(SpriteBatch& batch);
		void draw(SpriteBatch& batch, bool flipH, bool flipV);

		/**
			Append string to the current text
		*/
		void append(const char *str);

		/**
		*/
		void format(const char *fmt, ...);

		/**
			Remove any text
		*/
		void clear(void);

		/**
		*/
		void removeBack();

		void setFont(BitmapFont*);
		BitmapFont *getFont(void) const;

		void setPosition(const Vector2f&);
		void setPosition(float x, float y);

		Vector2f& getPosition(void);

		void setDimensions(const Vector2f&);
		void setDimensions(float w, float h);

		Vector2f& getDimensions(void);

		void setColor(ColorRGBA32f& c);
		ColorRGBA32f getColor();

		/* Stream Operator */

		template<typename T>
		Text& operator<<(T t)
		{
			std::ostringstream os;
			os << t;

			append(os.str().c_str());

			return *this;
		}

	private:
		/* Types */

		//! Font Cell
		struct Cell
		{
			Rect quad;
			Texture::TextureRegion region;

			Cell(Rect& q, Texture::TextureRegion& r)
			{
				quad = q;
				region = r;
			}
		};

		BitmapFont* _font;

		Vector2f _position;
		Vector2f _offset;

		Vector2f _dimension;

		ColorRGBA32f _color;

		std::vector<Cell>* _cells;

	};
}

#endif
