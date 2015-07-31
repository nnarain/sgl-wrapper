
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

		void setPosition(const Vector2&);
		void setPosition(float x, float y);

		Vector2& getPosition(void);

		void setDimensions(const Vector2&);
		void setDimensions(float w, float h);

		Vector2& getDimensions(void);

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

		Vector2 _position;
		Vector2 _offset;

		Vector2 _dimension;

		ColorRGBA32f _color;

		std::vector<Cell>* _cells;

	};
}

#endif
