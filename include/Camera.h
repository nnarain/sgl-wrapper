
#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#endif

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "Geometry.h"

namespace sgl{

#ifdef _MSC_VER
	class DLLEXPORT Camera
#else
	class Camera
#endif
	{
	public:
		Camera(void);
		Camera(float fov, float viewportWidth, float viewportHeight);
		~Camera(void);

		void update();

		void translate(float, float, float);
		void translate(glm::vec3);

		void lookAt(glm::vec3);
		void lookAt(float, float, float);

		void setPosition(glm::vec3);
		void setPosition(float, float, float);

		Ray pickRay(float viewportX, float viewportY);

		glm::mat4 combined();
		glm::mat4 projection();
		glm::mat4 view();
		glm::vec3 direction() const;

		//glm::mat4 inverseProjection();
		//glm::mat4 inverseView();

	private:
		glm::vec3 _pos;
		glm::vec3 _target;

		glm::mat4 _proj;
		glm::mat4 _view;

		glm::mat4 _inverseProj;
		bool _calcInverseProj;

		glm::mat4 _inverseView;
		bool _calcInverseView;

		float _viewportWidth;
		float _viewportHeight;

		float _nearClipping;
		float _farClipping;

	};
};

#endif

