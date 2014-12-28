
#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include "SGLExport.h"

#include "Texture.h"
#include "Geometry.h"

// math
#include <glm/vec2.hpp>

namespace sgl
{
	/**
		Represents a 2D image on the screen using pixel coordinates and dimensions
	*/
	SGLCLASS Sprite
	{
	public:
		/**
			@param x
				x pixel coordinate
			@param y
				y pixel coordinate
			@param width
				pixel width of the sprite
			@param height
				pixel height of the sprite
			@param tex
				The texture that the sprite uses
		*/
		Sprite(float x, float y, float width, float height, Texture* tex);
		~Sprite();

		glm::vec2 getPosition();

		float getWidth();
		float getHeight();

		Texture* getTexture();

		void setTextureRegion(float x, float y, float w, float h);
		Texture::TextureRegion* getTextureRegion();

	private:
		//! 2D position
		glm::vec2 _pos;
		//! pixel width
		float _width;
		//! pixel height
		float _height;

		//! texture that the sprite uses
		Texture* _texture;
		//! The region of the texture that the sprite uses
		Texture::TextureRegion _region;
	};
};

#endif
