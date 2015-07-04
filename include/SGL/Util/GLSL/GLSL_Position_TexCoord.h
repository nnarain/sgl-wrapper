
#ifndef GLSL_POSITION_TEXCOORD_H
#define GLSL_POSITION_TEXCOORD_H

#define GLSL(src) "\n" #src

#include <string>

namespace sgl
{
	const std::string GLSL_POSITION_TEXCOORD_VERT = GLSL(

		in vec2 vPosition;
		in vec2 vTexCoord;

		out vec2 fTexCoord;

		void main()
		{
			gl_Position = vec4(vPosition, 0, 1);

			fTexCoord = vTexCoord;
		}

	);

	const std::string GLSL_POSITION_TEXCOORD_FRAG = GLSL(

		out vec4 fragColor;

		in vec2 fTexCoord;

		uniform sampler2D sampler;

		void main()
		{
			fragColor = texture(sampler, fTexCoord);
		}

	);
}

#endif
