#include "terrainRenderer.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "window.h"


TerrainRenderer::TerrainRenderer()
{
}


TerrainRenderer::~TerrainRenderer()
{
}


void TerrainRenderer::render(std::vector<Terrain> terrains, Shader *shader)
{
	for (auto terrain : terrains)
	{
		glBindVertexArray(terrain.getRawModel().getVaoID());
		// Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, terrain.getModelTexture().getTextureID());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);


		// Create and load model matrix into shader
		glm::mat4 model;
		int modelLoc2 = glGetUniformLocation(shader->getShaderID(), "model");
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model));

		shader->setFloat("specularStrength", terrain.getSpecularStrength());


		// Draw
		glDrawElements(GL_TRIANGLES, terrain.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindVertexArray(0);
	}
}



	


