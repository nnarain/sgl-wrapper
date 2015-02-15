
#include "SGL/SGL.h"

namespace sgl
{
	SGLBOOLFUNC init()
	{
		// init glew
		glewExperimental = true;
		if (glewInit() != GLEW_OK){
			return false;
		}

		return true;
	}
};
