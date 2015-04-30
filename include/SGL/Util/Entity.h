#pragma once

#include "SGLExport.h"

#include "SGL/Math/Math.h"

namespace sgl{

	/**
		Representation of a entity in 3D world space. (Translation, Rotation, Scale)
	*/
	SGLCLASS Entity
	{
	public:

		Entity(void);
		~Entity(void);

		void translate(const Vector3&);
		void translate(float x, float y, float z);

		void rotate(const Vector3&);
		void rotate(float, float, float);

		void scale(const Vector3&);
		void scale(float, float, float);
		void scale(float);

		void setPosition(float, float, float);
		void setPosition(const Vector3&);

	private:
		

	};
};