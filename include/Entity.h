#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

namespace sgl{

	/**
		Representation of a entity in 3D world space. (Translation, Rotation, Scale)
	*/
#ifdef _MSC_VER
	class DLLEXPORT Entity
#else
	class Entity
#endif
	{
	public:

		Entity(void);
		~Entity(void);

		void translate(glm::vec3);
		void translate(float x, float y, float z);

		void rotate(glm::vec3);
		void rotate(float, float, float);

		void scale(glm::vec3);
		void scale(float, float, float);

		void setPosition(float, float, float);
		void setPosition(glm::vec3);

		glm::vec3 getPosition();
		glm::mat4 getRotationMatrix();
		glm::mat4 getModelMatrix();
		glm::mat3 getNormalMatrix();

	private:
		glm::vec4 _pos;
		glm::vec3 _angle;
		glm::vec3 _scale;

		glm::mat4 _transform;
		bool _transformReCalcRequired;
		

	};
};