
#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "SGL/Util/SGLExport.h"
#include "SGL/Type/Geometry.h"

#include <glm/glm.hpp>

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
		Camera(const Camera&);
		Camera& operator=(Camera);
		friend void swap(Camera&, Camera&);
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

		/**
			@return the world space transform of the camera
		*/
		glm::mat4 transform();

		/* Setters & Getters */
		
		/**
		Sets world position of camera, (x,y,z)
		*/
		void setPosition(glm::vec3);

		/**
		Sets world position of camera, (x,y,z)
		*/
		void setPosition(float, float, float);
		glm::vec3 getPosition() const;

		glm::vec3 getTarget() const;

		glm::vec3 getUpVector() const;
		void setUpVector(glm::vec3 up);

		glm::vec3 getLookDirection() const;

		glm::vec3 getRightDirection() const;

	private:
		//! camera position
		glm::vec3* _pos;
		
		//! where the camera is pointed to
		glm::vec3* _target;
		
		//! cameras up vector
		glm::vec3* _up;
		//! cameras right vector
		glm::vec3* _right;
		// direction camera is looking
		glm::vec3* _look;

		//! camera projection
		glm::mat4* _proj;
		//! camera view
		glm::mat4* _view;

		//! field of view
		float _fov;
		//!
		float _viewportWidth;
		//!
		float _viewportHeight;

		//! near clipping distance
		float _nearClipping;
		//! far clipping distance
		float _farClipping;

	};
};

#endif

