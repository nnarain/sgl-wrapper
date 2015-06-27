
#ifndef GLSL_POSITION_COLOR_H
#define GLSL_POSITION_COLOR_H

#include <string>

#define GLSL(src) "\n" #src

namespace sgl
{
	const std::string GLSL_POSITION_COLOR_VERT = GLSL(

		in vec3 vPosition;
		in vec3 vColor;

		out vec3 fColor;

		uniform mat4 VP;

		void main()
		{
			gl_Position = VP * vec4(vPosition, 1);

			fColor = vColor;
		}
	);

	const std::string GLSL_POSITION_COLOR_FRAG = GLSL(

		out vec3 fragColor;

		in vec3 fColor;

		void main()
		{
			fragColor = fColor;
		}
	);
}

#endif
