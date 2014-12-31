
#include "SGL/SpriteBatch.h"

#include <algorithm>

using namespace sgl;

/** Glyph Constructor */

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

/* Sort glyphs */
static bool sortGlyphs(SpriteBatch::Glyph* glyph1, SpriteBatch::Glyph* glyph2);

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
}

void SpriteBatch::begin(ShaderProgram* shader)
{
	_shader = shader;
	_shader->begin();
}

void SpriteBatch::draw(Sprite& sprite)
{
	// use the sprites quad and region to create 4 textured vertices for the Quad that will be drawn

	Quad                   &quad    = sprite.getQuad();
	Texture::TextureRegion &region  = sprite.getTextureRegion();
	Texture                *texture = sprite.getTexture();

	_glyphs->emplace_back(quad, region, texture);

	//Glyph* pGlyph = &((*_glyphs)[_glyphs->size() - 1]);
	//Glyph* pGlyph = &_glyphs->back();
	//_glyphPointers->push_back(pGlyph);

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

SpriteBatch::~SpriteBatch()
{
	delete _glyphs;
	delete _glyphPointers;
}

static bool sortGlyphs(SpriteBatch::Glyph* glyph1, SpriteBatch::Glyph* glyph2)
{
	return glyph1->texture->handle() < glyph2->texture->handle();
}