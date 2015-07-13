
#ifndef COLOR_H
#define COLOR_H

#include "SGL/Util/SGLExport.h"

#include <cstdint>

namespace sgl
{
	template<typename T>
	SGLCLASS ColorRGBA
	{
	public:

		T r;
		T g;
		T b;
		T a;

	public:
		ColorRGBA(T r, T g, T b, T a) : r(r), g(g), b(b), a(a)
		{
		}

		ColorRGBA(T r, T g, T b) : ColorRGBA<T>(r, g, b, 1)
		{
		}

		ColorRGBA() : ColorRGBA<T>(0, 0, 0, 0)
		{
		}

		ColorRGBA operator+(ColorRGBA<T>& c)
		{
			return ColorRGBA<T>(this->r + c.r, this->g + c.g, this->b + c.b, this->a + c.a);
		}
		ColorRGBA operator-(ColorRGBA<T>& c)
		{
			return ColorRGBA<T>(this->r - c.r, this->g - c.g, this->b - c.b, this->a - c.a);
		}

		ColorRGBA operator*(ColorRGBA<T>& c)
		{
			return ColorRGBA<T>(this->r * c.r, this->g * c.g, this->b * c.b, this->a * c.a);
		}

		ColorRGBA operator*(T value)
		{
			return ColorRGBA<T>(this->r * value, this->g * value, this->b * value, this->a * value);
		}


	private:

	};

	template<typename T>
	SGLCLASS ColorRGB
	{
	public:

		T r;
		T g;
		T b;

	public:
		ColorRGB(T r, T g, T b) : r(r), g(g), b(b)
		{
		}

		ColorRGB() : ColorRGB<T>(0, 0, 0)
		{
		}

		ColorRGB operator+(ColorRGB<T>& c)
		{
			return ColorRGB<T>(this->r + c.r, this->g + c.g, this->b + c.b);
		}
		ColorRGB operator-(ColorRGB<T>& c)
		{
			return ColorRGB<T>(this->r - c.r, this->g - c.g, this->b - c.b);
		}

		ColorRGB operator*(ColorRGB<T>& c)
		{
			return ColorRGB<T>(this->r * c.r, this->g * c.g, this->b * c.b);
		}

		ColorRGB operator*(T value)
		{
			return ColorRGB<T>(this->r * value, this->g * value, this->b * value);
		}


	private:

	};

	typedef ColorRGBA<float>   ColorRGBA32f;
	typedef ColorRGBA<uint8_t> ColorRGBA8i;

	typedef ColorRGB<float>    ColorRGB32f;
	typedef ColorRGB<uint8_t>  ColorRGB8i;
}

#endif