SGL Wrapper
===========

Simple OpenGL Wrapper. A, very light weight and simplistic, C++ wrapper library around OpenGL's C function calls.


Features
--------

* Camera
* ShaderProgram
* Basic representation of 3D models
	* translation, rotation, scaling
	* vertex attributes (position, normals, texutures)

This library is intended for simple projects.


Build
-----

Dependencies: GLEW, GLM

Builds with CMake

Examples
--------

TODO
----
* Clean up API. Remove need for unnecessary classes (i.e. VertexAttribute can be a structure in VertexAttributeSet)
* Add Texture and Material types
* Load ShaderProgram can load itself from files
* Make examples