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
* Sprites, SpriteSheets and SpriteBatching


Build
-----

Dependencies: GLEW, GLM

Builds with CMake

Note: This library compiles with Visual C++, GNU compiler **will not** work (yet).

This command should do the trick:

```bash
/> cmake -G "Visual Studio 12" C:\path\to\src
```

Examples
--------

TODO
----
* Orthographic and Perspective Camera?
* Camera Controller
* Test with Qt and on Linux
* Make examples