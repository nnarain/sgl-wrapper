SGL Wrapper
===========

Simple OpenGL Wrapper. A, very light weight and simplistic, C++ library for creating simple opengl projects.


Features
--------

* Camera
* ShaderProgram
* Basic representation of 3D models
	* translation, rotation, scaling
	* vertex attributes (position, normals, texutures, colors)
* Textures, FrameBuffers
* Selection
	* Ray picking using spheres


Build
-----

Dependencies: GLEW, GLM

Builds with CMake

Examples
--------

TODO
----
* Camera Controller (Useful helper class)
* Orthographic and Perspective Camera
* Helpers for mesh creation (Cube, Triangles, Quads, Sphere, Wireframe?)
	* Quads can use screen coordinates and convert to normalized device coordinates
* Remove Bounding Box?
* Test with Qt and on Linux
* Make examples