#include "RenderableEntity.h"

using namespace sgl;

const char* RenderableEntity::POSITION = "a_position";
const char* RenderableEntity::NORMAL = "a_normal";

RenderableEntity::RenderableEntity(StaticModel* m)
{
	model = m;
}

/*

void RenderableEntity::render(ShaderProgram* shader)
{
	// compute the model view projection matrix
	glm::mat4 mvp = shader->getProjectionView() * getModelMatrix();
	// get the position location
	GLuint a_position = shader->getAttributeLocation(RenderableEntity::POSITION);
	GLuint mvpID = shader->getUniformLocation("mvp");

	// pass mvp to shader
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

	int i;
	for (i = 0; i < model->numMeshes; i++){

		glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
		glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ibos[i]);
		glDrawElements(GL_TRIANGLES, model->numIndices[i], GL_UNSIGNED_INT, NULL);

	}

}
*/

RenderableEntity::~RenderableEntity(void)
{

}
