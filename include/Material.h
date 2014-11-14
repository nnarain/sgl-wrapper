
#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include <cmath>
#include <glm/vec4.hpp>

namespace sgl{

	struct Color{
		float r;
		float g;
		float b;
		float a;

		Color() :r(0), g(0), b(0), a(0)
		{}

		void set(unsigned char R, unsigned char G, unsigned char B, unsigned A)
		{
			r = R;
			g = G;
			b = B;
			a = A;
			normalize();
		}

		void normalize()
		{
			float mag = sqrt((r*r) + (g*g) + (b*b));
			r = (1 / mag) * r;
			g = (1 / mag) * g;
			b = (1 / mag) * b;
			a = (1 / mag) * a;
		}

		glm::vec4 toVec()
		{
			return glm::vec4(r,g,b,a);
		}
		
	};

	struct Material{
		Color ambient;
		Color diffuse;
		Color specular;
	};

};

#endif

