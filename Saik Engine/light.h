#pragma once

#include "entity.h"
#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	~Light();

	glm::vec3 getPosition() { return position; }
	glm::vec3 getColor() { return color; }
	Entity getEntity() {return lightEntity;}

private:
	Entity lightEntity;
	glm::vec3 position;
	glm::vec3 color;
};

