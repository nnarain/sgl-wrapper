
#include "SGL/SpriteBatch.h"
#include "SGL/SGLException.h"

#include <algorithm>
#include <cassert>

using namespace sgl;

/** Glyph Constructors */

SpriteBatch::Glyph::Glyph()
{
}

SpriteBatch::Glyph::Glyph(Quad& quad, Texture::TextureRegion& region, Texture* t)
{
	texture     = t;

	v1.pos      = quad.bottomLeft;
	v1.texCoord = region.bottomLeft;

	v2.pos      = quad.topLeft;
	v2.texCoord = region.topLeft;

	v3.pos      = quad.topRight;
	v3.texCoord = region.topRight;

	v4.pos      = quad.bottomRight;
	v4.texCoord = region.bottomRight;
}

/* SpriteBatch */

SpriteBatch::SpriteBatch()
{
	_mesh = new Mesh(GL_TRIANGLES, 0, GL_STREAM_DRAW);

	// bind position and texture coordinate attributes
	_mesh->addAttribute(VertexAttribute(0, 2));
	_mesh->addAttribute(VertexAttribute(1, 2));

	//
	_glyphs = new std::vector<Glyph>();
	_glyphPointers = new std::vector<Glyph*>();

	//
	_isActive = false;
}

void SpriteBatch::begin(ShaderProgram* shader)
{
	assert(shader != NULL && "SpriteBatch::begin : NULL Shader!");

	_shader = shader;
	_shader->begin();

	_isActive = true;
}

void SpriteBatch::draw(Sprite& sprite)
{
	// call the base draw with the sprite's quad, region and texture

	Quad                   &quad    = sprite.getQuad();
	Texture::TextureRegion &region  = sprite.getTextureRegion();
	Texture                *texture = sprite.getTexture();

	draw(quad, region, texture);
}

void SpriteBatch::draw(Sprite& sprite, bool flipH, bool flipV)
{
	// call the base draw with the sprite's quad, region and texture.
	// flip on the specified axis'

	Quad                   &quad    = sprite.getQuad();
	Texture::TextureRegion region   = sprite.getTextureRegion();
	Texture                *texture = sprite.getTexture();

	flip(region, flipH, flipV);

	draw(quad, region, texture);
}

void SpriteBatch::draw(Quad& quad, Texture::TextureRegion& region, Texture* texture)
{
	assert(_isActive && "SpriteBatch::draw : SpriteBatch has not been started!");

	_glyphs->emplace_back(quad, region, texture);
}

void SpriteBatch::renderBatch()
{
	if (_glyphPointers->size() == 0) return;

	// sort glyphs by texture handle
	std::sort(_glyphPointers->begin(), _glyphPointers->end(), sortGlyphs);

	Texture* currentTexture = (*_glyphPointers)[0]->texture;
	std::vector<Vertex> batch;

	// iterate over the glyphs
	std::vector<Glyph*>::iterator iter;
	for (iter = _glyphPointers->begin(); iter != _glyphPointers->end(); ++iter)
	{
		Glyph* glyph = (*iter);

		// when the texture changes render the batch
		if (glyph->texture != currentTexture)
		{
			render(currentTexture, &batch);
			currentTexture = glyph->texture;
		}

		/*
			Batch quads of same texture

			Create the 2 triangles that make up the quad of the sprite

			1st Triangle - v2, v1, v4
			2nd Triangle - v2, v4, v3

		*/

		batch.push_back(glyph->v2);
		batch.push_back(glyph->v1);
		batch.push_back(glyph->v4);

		batch.push_back(glyph->v2);
		batch.push_back(glyph->v4);
		batch.push_back(glyph->v3);

	}

	// render the last batch
	render(currentTexture, &batch);

	// clear
	_glyphPointers->clear();
	_glyphs->clear();
}

void SpriteBatch::render(Texture* texture, std::vector<Vertex> *batch)
{
	if (texture == NULL) return;

	texture->bind(GL_TEXTURE0);

	int size = batch->size();

	// update the mesh data and draw count
	_mesh->create(&(*batch)[0], size * sizeof(Vertex), sizeof(Vertex));
	_mesh->setDrawCount(size);

	// bind the batched mesh and draw the vertices
	_mesh->bind();
	_mesh->draw();
	_mesh->unbind();

	// clear the batch so its ready for the next
	batch->clear();
}

void SpriteBatch::end()
{
	assert(_isActive && "SpriteBatch::end : SpriteBatch has not been started!");

	// add glyph pointers to buffer
	int size = _glyphs->size();
	int i;
	for (i = 0; i < size; ++i)
	{
		_glyphPointers->push_back(&_glyphs->at(i));
	}

	// begin the render process
	{
		_shader->uniform("texture", 0);
		renderBatch();
	}
	_shader->end();

	_shader = NULL;
}

void SpriteBatch::flip(Texture::TextureRegion& region, bool horizontal, bool vertical)
{
	// flip on the vertical axis
	if (vertical)
	{
		// swap top left with top right, and bottom left with bottom right
		// to vertically flip the region on the quad

		// tmp vars
		glm::vec2 tl = region.topLeft;
		glm::vec2 bl = region.bottomLeft;

		// swap
		region.topLeft = region.topRight;
		region.bottomLeft = region.bottomRight;
		region.topRight = tl;
		region.bottomRight = bl;
	}

	// flip on the horizontal axis
	if (horizontal)
	{
		// swap the top left with bottom left and top right with bottom right
		// to horizontally flip the region on the quad

		// tmp vars
		glm::vec2 bl = region.bottomLeft;
		glm::vec2 br = region.bottomRight;

		// swap
		region.bottomLeft = region.topLeft;
		region.bottomRight = region.topRight;
		region.topLeft = bl;
		region.topRight = br;
	}
}

bool SpriteBatch::sortGlyphs(SpriteBatch::Glyph* glyph1, SpriteBatch::Glyph* glyph2)
{
	return glyph1->texture->handle() < glyph2->texture->handle();
}

SpriteBatch::~SpriteBatch()
{
	delete _glyphs;
	delete _glyphPointers;
	delete _mesh;
}
