
#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace sgl{

#ifdef _MSC_VER
	class DLLEXPORT Camera
#else
	class Camera
#endif
	{
	public:
		Camera(void);
		Camera(float fov, float aspectRatio);
		~Camera(void);

		void update();

		void translate(float, float, float);
		void translate(glm::vec3);

		void lookAt(glm::vec3);
		void lookAt(float, float, float);

		void setPosition(glm::vec3);
		void setPosition(float, float, float);

		glm::mat4 combined();
		glm::mat4 getProjectionMatrix();
		glm::mat4 getViewMatrix();

	private:
		glm::vec3 pos;
		glm::vec3 target;

		glm::mat4 proj;
		glm::mat4 view;

	};
};

#endif

