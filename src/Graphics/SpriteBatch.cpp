
#include "SGL/Graphics/SpriteBatch.h"
#include "SGL/Util/Exception.h"
#include "SGL/Util/Context.h"

#include <algorithm>
#include <cassert>

using namespace sgl;

/** Glyph Constructors */

SpriteBatch::Glyph::Glyph()
{
}

SpriteBatch::Glyph::Glyph(Vertex& v1, Vertex& v2, Vertex& v3, Vertex& v4, Texture* t) : v1(v1), v2(v2), v3(v3), v4(v4), texture(t)
{
}

/* SpriteBatch */

SpriteBatch::SpriteBatch() :
	_mesh(Mesh::Type::TRIANGLES, 0, Buffer::Usage::STREAM_DRAW),
	_shader(NULL),
	_glyphs(new std::vector<Glyph>),
	_glyphPointers(new std::vector<Glyph*>)
{
	// bind position and texture coordinate attributes
	_mesh.addAttribute(VertexAttribute(0, 2));
	_mesh.addAttribute(VertexAttribute(1, 2));
	_mesh.addAttribute(VertexAttribute(2, 4));

	_mesh.create(sizeof(Vertex));
}

void SpriteBatch::begin(ShaderProgram* shader)
{
	assert(shader != NULL && "SpriteBatch::begin : NULL Shader!");

	_shader = shader;
	_shader->begin();
}

void SpriteBatch::draw(Sprite& sprite)
{
	// call the base draw with the sprite's quad, region and texture

	Rect                   &quad    = sprite.getQuad();
	Texture::TextureRegion &region  = sprite.getTextureRegion();
	ColorRGBA32f           &color = sprite.getColor();
	Texture                *texture = sprite.getTexture();

	draw(quad, region, color, texture);
}

void SpriteBatch::draw(Sprite& sprite, bool flipH, bool flipV)
{
	// call the base draw with the sprite's quad, region and texture.
	// flip on the specified axis'

	Rect                   &quad    = sprite.getQuad();
	Texture::TextureRegion region   = sprite.getTextureRegion();
	ColorRGBA32f&          color = sprite.getColor();
	Texture                *texture = sprite.getTexture();

	flip(region, flipH, flipV);

	draw(quad, region, color, texture);
}

void SpriteBatch::draw(Rect& rect, Texture::TextureRegion& region, Texture* texture)
{
	draw(rect, region, ColorRGBA32f(1, 1, 1, 1), texture);
}

void SpriteBatch::draw(Rect& rect, Texture::TextureRegion& region, Texture* texture, bool flipH, bool flipV)
{
	draw(rect, region, ColorRGBA32f(1, 1, 1, 1), texture, flipH, flipV);
}

void SpriteBatch::draw(Rect& rect, Texture::TextureRegion& region, ColorRGBA32f& color, Texture* texture, bool flipH, bool flipV)
{
	Texture::TextureRegion r(region);
	flip(r, flipH, flipV);

	draw(rect, r, color, texture);
}

void SpriteBatch::draw(Rect& rect, Texture* texture)
{
	draw(rect, texture->region(0, 0, -1, -1), texture);
}

void SpriteBatch::draw(Rect& rect, Texture::TextureRegion& region, ColorRGBA32f& color, Texture* texture)
{
	Vertex v1, v2, v3, v4;

	// bottom left
	v1.pos      = Context::pixelToNDC(rect.x, rect.y);
	v1.texCoord = region.bottomLeft;
	v1.color    = color;

	// top left
	v2.pos      = Context::pixelToNDC(rect.x, rect.y + rect.height);
	v2.texCoord = region.topLeft;
	v2.color    = color;

	// top right
	v3.pos      = Context::pixelToNDC(rect.x + rect.width, rect.y + rect.height);
	v3.texCoord = region.topRight;
	v3.color    = color;

	// bottom right
	v4.pos      = Context::pixelToNDC(rect.x + rect.width, rect.y);
	v4.texCoord = region.bottomRight;
	v4.color    = color;

	//_glyphs->emplace_back(rect, region, color, texture);
	_glyphs->emplace_back(v1, v2, v3, v4, texture);
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

	texture->bind(Texture::Unit::T0);

	int size = batch->size();

	// update the mesh data and draw count
	Buffer &vbo = _mesh.getVBO();
	vbo.bind();
	vbo.setData(&(*batch)[0], size * sizeof(Vertex));
	vbo.unbind();

	_mesh.setDrawCount(size);

	// bind the batched mesh and draw the vertices
	_mesh.bind();
	_mesh.draw();
	_mesh.unbind();

	// clear the batch so its ready for the next
	batch->clear();
}

void SpriteBatch::end()
{
	assert(_shader != NULL && "Shader program is null!");

	// add glyph pointers to buffer
	int size = _glyphs->size();
	int i;
	for (i = 0; i < size; ++i)
	{
		_glyphPointers->push_back(&_glyphs->at(i));
	}

	// begin the render process
	{
		(*_shader)["sampler"].set(0);
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
		std::swap(region.topLeft, region.topRight);
		std::swap(region.bottomLeft, region.bottomRight);
	}

	// flip on the horizontal axis
	if (horizontal)
	{
		// swap the top left with bottom left and top right with bottom right
		// to horizontally flip the region on the quad
		std::swap(region.topLeft, region.bottomLeft);
		std::swap(region.topRight, region.bottomRight);
	}
}

bool SpriteBatch::sortGlyphs(SpriteBatch::Glyph* glyph1, SpriteBatch::Glyph* glyph2)
{
	return glyph1->texture->getId() < glyph2->texture->getId();
}

SpriteBatch::~SpriteBatch()
{
	delete _glyphs;
	delete _glyphPointers;
}
