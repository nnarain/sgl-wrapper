#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

namespace sgl{

#ifdef _MSC_VER
	class DLLEXPORT Entity
#else
	class Entity
#endif
	{
	public:

		const static char* POSITION;
		const static char* NORMAL;

		Entity(void);
		~Entity(void);

		void translate(glm::vec3);
		void translate(float x, float y, float z);

		void rotate(glm::vec3);
		void rotate(float, float, float);

		void setPosition(float, float, float);
		void setPosition(glm::vec3);

		glm::vec3 getPosition();
		glm::mat4 getModelMatrix();

	private:
		glm::vec4 pos;
		glm::vec3 angle;

	};
};