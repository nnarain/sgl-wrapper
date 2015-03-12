

#ifndef UNIFORM_H
#define UNIFORM_H

#include <SGL/Util/SGLExport.h>
#include <SGL/GL/Texture.h>
#include <glm/glm.hpp>

namespace sgl
{
	/**
		Wrapper from GLSL uniform functions
	*/
	SGLCLASS Uniform
	{
	public:

		Uniform(int location);
		~Uniform(void);

		/* Set functions */

		void set(int);
		void set(int, int);
		void set(int, int, int);
		void set(int, int, int, int);

		void set(float);
		void set(float, float);
		void set(float, float, float);
		void set(float, float, float, float);

		void set(const glm::vec3 &);
		void set(const glm::vec4 &);

		void set(const glm::mat3 &);
		void set(const glm::mat3 &, bool transpose);

		void set(const glm::mat4 &);
		void set(const glm::mat4 &, bool transpose);

		void set(const Texture &);

		/* Getters */
		int getLocation() const;

	private:
		int _location;

	};
};

#endif
