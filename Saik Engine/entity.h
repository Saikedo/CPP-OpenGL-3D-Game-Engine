#pragma once

#include "texturedModel.h"
#include <glm/glm.hpp>

class Entity
{
public:
	Entity(TexturedModel texturedModel, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);

	~Entity();

	void increasePosition(float dx, float dy, float dz);

	void increaseRotation(float dx, float dy, float dz);

	TexturedModel getTexturedModel() { return model; }

	glm::vec3 getPosition() { return position; }
	glm::vec3 getRotation() { return glm::vec3(rotX, rotY, rotZ);}
	float getScale() { return scale; }


	void changePosition(glm::vec3 dPosition) { position += dPosition;  }
	void changeRotation(glm::vec3 dRotation)
	{
		rotX += dRotation.x;
		rotY += dRotation.y;
		rotZ += dRotation.z;
	}

private:
	TexturedModel model;
	glm::vec3 position;
	float rotX, rotY, rotZ;
	float scale;
};

