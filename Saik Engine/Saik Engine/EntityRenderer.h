#pragma once

#include "entity.h"
#include "Shader.h"
#include <vector>


class EntityRenderer
{
public:
	EntityRenderer();
	~EntityRenderer();

	void Render(std::vector<Entity> entities, Shader *shader);
};

