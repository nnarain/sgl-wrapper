SGL Wrapper
===========

Simple OpenGL Wrapper. A simple object oriented wrapper for OpenGL.


Features
--------

* Camera
* ShaderProgram
* Basic representation of 3D models
	* translation, rotation, scaling
	* vertex attributes (position, normals, texutures, colors)
* Textures
* Frame buffers and Render buffers
* Sprites, SpriteSheets and SpriteBatching


Build
-----

Dependencies: GLEW, GLM

Builds with CMake

Note: This library compiles with Visual C++, GNU compiler **will not** work (yet).

This command should do the trick:

```bash
/> cmake -G "Visual Studio 12" C:\path\to\project
```

Examples
--------

TODO
----
* Test with Qt and on Linux
* Make examples