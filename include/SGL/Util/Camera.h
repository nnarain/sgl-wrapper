
#ifndef CAMERA_H
#define CAMERA_H

#include "SGL/Util/SGLExport.h"
#include "SGL/Type/Geometry.h"

#include "SGL/Math/Vector3.h"
#include "SGL/Math/Matrix4.h"

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
		void lookAt(const Vector3 &);
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
		void setPosition(const Vector3&);

		/**
			Sets world position of camera, (x,y,z)
		*/
		void setPosition(float, float, float);

		/**
			Get the camera position
		*/
		Vector3& getPosition();

		/**
			Get the cameras lookat position
		*/
		const Vector3& getTarget() const;

		/**
			Get the camera directions
		*/
		Vector3 getDirection();

		/***/
		const Vector3& getUpVector() const;
		void setUpVector(const Vector3& up);

	protected:

		//! camera position
		Vector3 _pos;
		
		//! where the camera is pointed to
		Vector3 _target;
		
		//! cameras up vector
		Vector3 _up;

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

	};
};

#endif

