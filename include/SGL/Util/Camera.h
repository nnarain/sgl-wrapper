
#ifndef CAMERA_H
#define CAMERA_H

#include "SGL/Util/SGLExport.h"

#include "SGL/Math/Vector3.h"
#include "SGL/Math/Matrix4.h"
#include "SGL/Math/Ray.h"

namespace sgl{

	/**
		A Camera in the OpenGL enviroment. Defines what will be rendered in the window
	*/
	SGLCLASS Camera
	{
	public:
		Camera(void);
		Camera(float viewportWidth, float viewportHeight);
		

		~Camera(void);

		/**
			Recalculate camera matrices
		*/
		void update();

		/**
			point camera to (x,y,z)
		*/
		void lookAt(const Vector3f &);
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
		Matrix4 combined();

		/**
			@return the camera projection matrices
		*/
		const Matrix4& projection() const;

		/**
			@return the camera's view matrices
		*/
		const Matrix4& view() const;

		/* Setters & Getters */
		
		/**
			Sets world position of camera, (x,y,z)
		*/
		void setPosition(const Vector3f&);

		/**
			Sets world position of camera, (x,y,z)
		*/
		void setPosition(float, float, float);

		/**
			Get the camera position
		*/
		Vector3f& getPosition();

		/**
			Get the cameras lookat position
		*/
		const Vector3f& getTarget() const;

		/**
			Get the camera directions
		*/
		Vector3f getDirection();

		/**
			Get the cameras up vector
		*/
		const Vector3f& getUpVector() const;
		
		/**
			Set the cameras up vector
		*/
		void setUpVector(const Vector3f& up);

		/**
		*/
		float getViewPortWidth(void) const;

		/**
		
		*/
		float getViewPortHeight(void) const;

		/**
			Get the cameras far clipping distance
		*/
		float getFarClipping() const;

		/**
			Get the cameras near clipping distance
		*/
		float getNearClipping() const;

	protected:

		//! camera position
		Vector3f _pos;
		
		//! where the camera is pointed to
		Vector3f _target;
		
		//! cameras up vector
		Vector3f _up;

		//! camera projection
		Matrix4 _proj;
		
		/* 
			camera view matrix
		
			| right.x   up.x   forward.x   position.x |
			| right.y   up.y   forward.y   position.x |
			| right.z   up.z   forward.z   position.x |
			|   0        0         0           0      |

		*/
		Matrix4 _view;

		//!
		float _viewportWidth;
		//!
		float _viewportHeight;

		//! near clipping distance
		float _zNear;
		//! far clipping distance
		float _zFar;

		//! camera requires an update
		bool _dirty;

	private:

		/* Private member functions */

		void calculateViewMatrix(void);

		void updateViewPort();

	};
};

#endif

