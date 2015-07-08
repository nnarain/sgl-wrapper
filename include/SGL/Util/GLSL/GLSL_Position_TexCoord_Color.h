
#ifndef GLSL_POSITION_TEXCOORD_H
#define GLSL_POSITION_TEXCOORD_H

#define GLSL(src) "\n" #src

#include "SGL/GL/ShaderProgram.h"

#include <string>

namespace sgl
{
	const std::string GLSL_POSITION_TEXCOORD_COLOR_VERT = GLSL(

		in vec2 vPosition;
		in vec2 vTexCoord;
		in vec4 vColor;

		out vec2 fTexCoord;
		out vec4 fColor;

		void main()
		{
			gl_Position = vec4(vPosition, 0, 1);

			fTexCoord = vTexCoord;
			fColor    = vColor;
		}

	);

	const std::string GLSL_POSITION_TEXCOORD_COLOR_FRAG = GLSL(

		out vec4 fragColor;

		in vec2 fTexCoord;
		in vec4 fColor;

		uniform sampler2D sampler;

		void main()
		{
			fragColor = texture(sampler, fTexCoord) * fColor;
		}

	);

	namespace loadshader
	{
		void position_texCoord_color(ShaderProgram& shader)
		{
			shader.load(ShaderProgram::Type::VERTEX,   GLSL_POSITION_TEXCOORD_COLOR_VERT);
			shader.load(ShaderProgram::Type::FRAGMENT, GLSL_POSITION_TEXCOORD_COLOR_FRAG);
			shader.addAttribute("vPosition", 2);
			shader.addAttribute("vTexCoord", 2);
			shader.addAttribute("vColor",    4);

			shader.link();
		}
	}
}

#endif
