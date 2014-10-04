
#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include "Vector3f.h"
#include <glm/mat4x4.hpp>

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
		void translate(Vector3f);

		void lookAt(Vector3f);
		void lookAt(float, float, float);

		void setPosition(Vector3f);
		void setPosition(float, float, float);

		glm::mat4 combined();
		glm::mat4 getProjectionMatrix();
		glm::mat4 getViewMatrix();

	private:
		Vector3f pos;
		Vector3f target;

		glm::mat4 proj;
		glm::mat4 view;

	};
};

#endif

