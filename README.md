SGL Wrapper
===========

Simple OpenGL Wrapper. A simple object oriented interface to OpenGL.


**The OpenGL Interface includes**

* Camera
* Shaders
* Textures
* Framebuffers
* Uniforms
* Mesh
	* bind and draw vertex data

**Utilities**

* Auto Image loading
	* Bitmap, TGA
* Wavefront Object Loader

Build
-----

Dependencies: GLEW, GLM

Builds with CMake

Note: This library must be compiled with C++11

This command should do the trick:

```bash
/> cmake -G "Visual Studio 12" C:\path\to\project
```

Examples
--------

TODO
----
* Wavefront Object format support?
* Test with Qt and on Linux
* Make examples