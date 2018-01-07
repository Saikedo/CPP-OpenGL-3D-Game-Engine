#include "masterRenderer.h"
#include "window.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


MasterRenderer::MasterRenderer()
{
	//  Create projectionMatrix
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(Camera::getCameraInstance()->getZoom()), 
		float(Window::getWindowInstance()->getWindowWidth()) / (float)(Window::getWindowInstance()->getWindowHeight()), 0.1f, 1000.0f);

	// Create EntityShader and EntityRenderer
	entityShader = new Shader("vertexShader.vert", "fragmentShader.frag");
	entityRenderer = new EntityRenderer();

	// Load ProjectionMatrix into EntityShader
	entityShader->start();
	glUniformMatrix4fv(glGetUniformLocation(entityShader->getShaderID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	entityShader->stop();

	// Create TerrainShader and TerrainRenderer
	terrainShader = new Shader("terrainVertexShader.vert", "terrainFragmentShader.frag");
	terrainRenderer = new TerrainRenderer();

	//Load projection matrix into TerrainShader
	terrainShader->start();
	glUniformMatrix4fv(glGetUniformLocation(terrainShader->getShaderID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	terrainShader->stop();
}


MasterRenderer::~MasterRenderer()
{
	delete entityShader;
	delete entityRenderer;
	delete terrainShader;
	delete terrainRenderer;
}


void MasterRenderer::render(Light light)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.2f, 0.4f, 1.0f);


	// Process all entities here
	entityShader->start();
	//glUniform1i(glGetUniformLocation(shader.getShaderID(), "texture1"), 0);


	//entityShader->setVec3("ambientLight", 0.1f, 0.1f, 0.1f);
	//entityShader->setVec3("lightPosition",light.getPosition());
	//entityShader->setVec3("lightColor", light.getColor());
	//entityShader->setVec3("viewPosition", Camera::getCameraInstance()->getPosition());
	// Load view matrix into entity shader
	glUniformMatrix4fv(glGetUniformLocation(entityShader->getShaderID(), "view"), 1, GL_FALSE, glm::value_ptr(Camera::getCameraInstance()->getCameraView()));

	entityRenderer->Render(entities, entityShader);

	entityShader->stop();

	

	// Process all terrains here
	terrainShader->start();
	//terrainShader->setVec3("ambientLight", 0.1f, 0.1f, 0.1f);
	//terrainShader->setVec3("lightPosition", light.getPosition());
	//terrainShader->setVec3("lightColor", light.getColor());
	//terrainShader->setVec3("viewPosition", Camera::getCameraInstance()->getPosition());
	// Load view matrix into terrain shader
	glUniformMatrix4fv(glGetUniformLocation(terrainShader->getShaderID(), "view"), 1, GL_FALSE, glm::value_ptr(Camera::getCameraInstance()->getCameraView()));

	terrainRenderer->render(terrains, terrainShader);
	terrainShader->stop();


	entities.clear();
	terrains.clear();
}

void MasterRenderer::prepareEntity(Entity entity)
{
	entities.emplace_back(entity);

}

void MasterRenderer::prepareTerrain(Terrain terrain)
{
	terrains.emplace_back(terrain);
}