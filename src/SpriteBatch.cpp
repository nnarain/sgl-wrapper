
#include "SGL/SpriteBatch.h"

#include <algorithm>

using namespace sgl;

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
	_glyphBuffer = new std::vector<Glyph*>();
}

void SpriteBatch::begin(ShaderProgram* shader)
{
	_shader = shader;
	_shader->begin();
}

void SpriteBatch::draw(Sprite& sprite)
{
	// use the sprites quad and region to create 4 textured vertices for the Quad that will be drawn

	Quad&                   quad   = sprite.getQuad();
	Texture::TextureRegion& region = sprite.getTextureRegion();

	Glyph* glyph = new Glyph;

	glyph->texture = sprite.getTexture();

	glyph->v1.pos      = quad.bottomLeft;
	glyph->v1.texCoord = region.bottomLeft;

	glyph->v2.pos      = quad.topLeft;
	glyph->v2.texCoord = region.topLeft;

	glyph->v3.pos      = quad.topRight;
	glyph->v3.texCoord = region.topRight;

	glyph->v4.pos      = quad.bottomRight;
	glyph->v4.texCoord = region.bottomRight;

	_glyphBuffer->push_back(glyph);
}

void SpriteBatch::renderBatch()
{
	if (_glyphBuffer->size() == 0) return;

	// sort glyphs by texture handle
	std::sort(_glyphBuffer->begin(), _glyphBuffer->end(), sortGlyphs);

	Texture* currentTexture = (*_glyphBuffer)[0]->texture;
	std::vector<Vertex> batch;

	// iterate over the glyphs
	std::vector<Glyph*>::iterator iter;
	for (iter = _glyphBuffer->begin(); iter != _glyphBuffer->end(); ++iter)
	{
		Glyph* glyph = (*iter);

		if (glyph->texture != currentTexture)
		{
			render(currentTexture, &batch);
			currentTexture = glyph->texture;
		}

		/*
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

		delete glyph;
	}

	// render the last batch
	if (currentTexture != NULL)
	{
		render(currentTexture, &batch);
	}

	_glyphBuffer->clear();
}

void SpriteBatch::render(Texture* texture, std::vector<Vertex> *batch)
{
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
	delete _glyphBuffer;
}

static bool sortGlyphs(SpriteBatch::Glyph* glyph1, SpriteBatch::Glyph* glyph2)
{
	return glyph1->texture->handle() < glyph2->texture->handle();
}