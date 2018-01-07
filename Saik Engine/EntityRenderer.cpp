#include "EntityRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "window.h"

EntityRenderer::EntityRenderer()
{
}


EntityRenderer::~EntityRenderer()
{
}


void EntityRenderer::Render(std::vector<Entity> entities, Shader *shader)
{
	for (auto entity : entities)
	{
		

		glBindVertexArray(entity.getTexturedModel().getRawModel().getVaoID());

		// Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity.getTexturedModel().getModelTexture().getTextureID());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Create and load model matrix into shader
		glm::mat4 model;
		model = glm::translate(model, entity.getPosition());
		model = glm::rotate(model, glm::radians(entity.getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(entity.getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(entity.getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(entity.getScale(), entity.getScale(), entity.getScale()));
		int modelLoc = glGetUniformLocation(shader->getShaderID(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		shader->setFloat("specularStrength", entity.getSpecularStrength());

		// Draw
		//glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindVertexArray(0);
	}
}