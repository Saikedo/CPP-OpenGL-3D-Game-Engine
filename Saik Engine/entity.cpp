#include "entity.h"



Entity::Entity(TexturedModel texturedModel, glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
{
	this->model = texturedModel;
	this->position = position;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
}


Entity::~Entity()
{
}


void Entity::increasePosition(float dx, float dy, float dz) {
	this->position.x += dx;
	this->position.y += dy;
	this->position.z += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz) {
	this->rotX += dx;
	this->rotY += dy;
	this->rotZ += dz;
}