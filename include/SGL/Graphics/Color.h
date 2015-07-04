
#ifndef COLOR_H
#define COLOR_H

#include "SGL/Util/SGLExport.h"

namespace sgl
{
	SGLCLASS Color
	{
	public:

		float r;
		float g;
		float b;
		float a;

	public:
		Color(float r, float g, float b, float a);
		Color(float r, float g, float b);

		Color operator+(Color&);
		Color operator-(Color&);
		Color operator*(Color&);
		Color operator*(float);

	private:

	};
}

#endif