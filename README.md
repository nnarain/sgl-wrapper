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
* Textures
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
* Specific Texture classes instead of generalized Texture class (i.e, Texture2D, CubeMapTextures, etc)
* Clean up Model (Mesh?) API. (VertexAttributes, etc)
* Lighting API? (Point, Directional, Cone)
* Helpers for mesh creation (Cube, Triangle, Sphere, Wireframe?)
* Test with Qt and on Linux
* Make examples