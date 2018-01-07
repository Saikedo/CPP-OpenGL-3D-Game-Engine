#pragma once

#include <vector>
#include "entity.h"
#include "EntityRenderer.h"
#include "Shader.h"
#include "terrainRenderer.h"
#include "terrain.h"
#include "light.h"

class MasterRenderer
{
public:
	MasterRenderer();
	~MasterRenderer();

	void prepareEntity(Entity entity);
	void prepareTerrain(Terrain terrain);
	void render(Light light);

private:
	std::vector<Entity> entities;
	std::vector<Terrain> terrains;
	Shader *entityShader;
	Shader *terrainShader;
	EntityRenderer *entityRenderer;
	TerrainRenderer *terrainRenderer;
};

