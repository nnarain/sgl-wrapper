
#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include "SGL/Util/SGLExport.h"

#include "SGL/GL/Texture.h"
#include "SGL/Math/Rect.h"
#include "SGL/Math/Vector2.h"
#include "SGL/Graphics/Color.h"

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

		void flip(bool h, bool v);

		void setPosition(Vector2f pos);
		void setPosition(float x, float y);
		Vector2f& getPosition();

		void setDimensions(float w, float h);

		Vector2f& getDimesions();
		float getWidth();
		float getHeight();

		Texture* getTexture();
		void setTexture(Texture *);

		void setTextureRegion(Texture::TextureRegion region);
		void setTextureRegion(float x, float y, float w, float h);
		Texture::TextureRegion& getTextureRegion();

		void setColor(const ColorRGBA32f& c);
		ColorRGBA32f& getColor();

		Rect& getQuad();

	private:
		//! 2D position
		Vector2f _pos;
		//! dimesions in pixels
		Vector2f _dim;

		//!
		ColorRGBA32f _color;

		//! texture that the sprite uses
		Texture* _texture;
		//! The region of the texture that the sprite uses
		Texture::TextureRegion _region;

		//! quad
		Rect _quad;
		//! flag to update the quad
		bool _updateQuad;
	};


};

#endif
