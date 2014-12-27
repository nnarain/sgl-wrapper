
#include "SGL/SpriteBatch.h"

#include <algorithm>

using namespace sgl;

/* Sort glyphs */
static bool sortGlyphs(SpriteBatch::Glyph* glyph1, SpriteBatch::Glyph* glyph2);

/* SpriteBatch */

SpriteBatch::SpriteBatch()
{
	_mesh = new Mesh(GL_TRIANGLES, 0, GL_STREAM_DRAW);
}

void SpriteBatch::begin(ShaderProgram* shader)
{
	_shader = shader;
}

void SpriteBatch::draw(Sprite& sprite)
{
	glm::vec2 pos = sprite.getPosition();
	Texture::TextureRegion* region = sprite.getTextureRegion();

	// make a quad with sprite dimensions and position
	Quad quad;
	sgl::util::makeQuad(quad, pos.x, pos.y, sprite.getWidth(), sprite.getHeight());

	/* 
		Create the 2 triangles that make up the quad of the sprite

		1st Triangle - v1, v2, v3
		2nd Triangle - v4, v5, v6

		v4 = v3
		v5 = v1

		So:
			1st Triangle - v1, v2, v3
			2nd Triangle - v3, v1, v4
	*/

	Glyph* glyph = new Glyph;

	glyph->texture = sprite.getTexture();

	glyph->v1.pos = quad.bottomLeft;
	glyph->v1.texCoord = (*region).bottomLeft;

	glyph->v2.pos = quad.topLeft;
	glyph->v2.texCoord = (*region).topLeft;

	glyph->v3.pos = quad.topRight;
	glyph->v3.texCoord = (*region).topRight;

	glyph->v4.pos = quad.bottomRight;
	glyph->v4.texCoord = (*region).bottomRight;

	_glyphBuffer.push_back(glyph);
}

void SpriteBatch::renderBatch()
{
	// sort glyphs by texture handle
	std::sort(_glyphBuffer.begin(), _glyphBuffer.end(), sortGlyphs);

	Texture* currentTexture = NULL;
	std::vector<Vertex> batch;

	// iterate over the glyphs
	std::vector<Glyph*>::iterator iter;
	for (iter = _glyphBuffer.begin(); iter != _glyphBuffer.end(); ++iter)
	{
		Glyph* glyph = (*iter);

		// if the glyph texture is the same, batch its vertices
		if (glyph->texture == currentTexture)
		{
			// push the 4 vertices in order to create 2 triangle that make up a quad

			batch.push_back(glyph->v1);
			batch.push_back(glyph->v2);
			batch.push_back(glyph->v3);

			batch.push_back(glyph->v3);
			batch.push_back(glyph->v1);
			batch.push_back(glyph->v4);
		}
		else
		{
			// glyph texture is not the same 
			// so we reached the end of these quads with the current texture
			// render the batch, change current texture and reset batch

			render(currentTexture, &batch);
			currentTexture = glyph->texture;

		}
	}
}

void SpriteBatch::render(Texture* texture, std::vector<Vertex> *batch)
{
	texture->bind(GL_TEXTURE0);

	_mesh->create(&(*batch)[0], batch->size() * sizeof(Vertex), sizeof(Vertex));
	_mesh->setDrawCount(0);

	_mesh->bind();
	_mesh->draw();
	_mesh->unbind();
}

void SpriteBatch::end()
{
	_shader->begin();
	{
		renderBatch();
	}
	_shader->end();
}

SpriteBatch::~SpriteBatch()
{
}

static bool sortGlyphs(SpriteBatch::Glyph* glyph1, SpriteBatch::Glyph* glyph2)
{
	return glyph1->texture->handle() < glyph2->texture->handle();
}