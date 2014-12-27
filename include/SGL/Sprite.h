
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
	SGLCLASS Sprite
	{
	public:
		Sprite(float x, float y, float w, float h, Texture* tex);
		~Sprite();

		glm::vec2 getPosition();

		float getWidth();
		float getHeight();

		Texture* getTexture();
		Texture::TextureRegion* getTextureRegion();

	private:
		glm::vec2 _pos;
		float _width;
		float _height;

		Texture* _texture;
		Texture::TextureRegion _region;
	};
};

#endif
