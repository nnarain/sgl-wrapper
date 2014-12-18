
#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "SGLExport.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "Picking.h"

namespace sgl{

	/**
		A Camera in the OpenGL enviroment. Defines what will be rendered in the window
	*/
	SGLCLASS Camera
	{
	public:
		Camera(void);

		/**
			Creates a camera with a field of view and viewport dimensions

			@param fov
				The field of view

			@param viewportWidth
				width of your view port

			@param viewportHeight
				height of your viewport
		*/
		Camera(float fov, float viewportWidth, float viewportHeight);
		~Camera(void);

		/**
			Recalculate camera matrices
		*/
		void update();

		/**
			point camera to (x,y,z)
		*/
		void lookAt(glm::vec3);
		/**
			point camera to (x,y,z)
		*/
		void lookAt(float, float, float);

		/**
			Sets world position of camera, (x,y,z)
		*/
		void setPosition(glm::vec3);

		/**
			Sets world position of camera, (x,y,z)
		*/
		void setPosition(float, float, float);

		/**
			@return a Ray pointing into the world given the screen coordinates
		*/
		Ray pickRay(float viewportX, float viewportY);

		/**
			@return the multiplied camera matrices
		*/
		glm::mat4 combined();

		/**
			@return the camera projection matrices
		*/
		glm::mat4 projection();

		/**
			@return the camera's view matrices
		*/
		glm::mat4 view();

		/**
			@return the direction of the camera
		*/
		glm::vec3 direction() const;

		glm::mat4 transform();

	private:
		//! camera position
		glm::vec3 _pos;
		//! where the camera is pointed to
		glm::vec3 _target;

		//! camera projection
		glm::mat4 _proj;
		//! camera view
		glm::mat4 _view;

		glm::mat4 _inverseProj;
		bool _calcInverseProj;

		glm::mat4 _inverseView;
		bool _calcInverseView;

		float _viewportWidth;
		float _viewportHeight;

		//! near clipping distance
		float _nearClipping;
		//! far clipping distance
		float _farClipping;

	};
};

#endif

