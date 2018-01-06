#pragma once

#include "terrain.h"
#include "Shader.h"
#include <vector>


class TerrainRenderer
{
public:
	TerrainRenderer();
	~TerrainRenderer();

	void render(std::vector<Terrain> terrains, Shader *shader);
};

