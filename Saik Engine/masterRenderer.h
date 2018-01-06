#pragma once

#include <vector>
#include "entity.h"
#include "EntityRenderer.h"
#include "Shader.h"
#include "terrainRenderer.h"
#include "terrain.h"

class MasterRenderer
{
public:
	MasterRenderer();
	~MasterRenderer();

	void prepareEntity(Entity entity);
	void prepareTerrain(Terrain terrain);
	void render();

private:
	std::vector<Entity> entities;
	std::vector<Terrain> terrains;
	Shader *entityShader;
	Shader *terrainShader;
	EntityRenderer *entityRenderer;
	TerrainRenderer *terrainRenderer;
};

