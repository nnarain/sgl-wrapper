

#ifndef UNIFORM_H
#define UNIFORM_H

#include <SGL/Util/SGLExport.h>
#include <SGL/GL/Texture.h>
#include <SGL/Math/Math.h>
#include <SGL/Graphics/Color.h>

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

		void set(const Vector2 &);
		void set(const Vector3 &);
		void set(const Vector4 &);

		void set(const Matrix3 &);
		void set(const Matrix3 &, bool transpose);

		void set(const Matrix4 &);
		void set(const Matrix4 &, bool transpose);

		void set(const Color&);

		void set(const Texture &);

		/* Getters */
		int getLocation() const;

	private:
		int _location;

	};
};

#endif
