#include "light.h"
#include "loader.h"
#include "cubeRawModel.h"

Light::Light(glm::vec3 position, glm::vec3 color)
{
	this->position = position;
	this->color = color;
	

	RawModel rawModel2 = CubeRawModel::getCubeRawModel();
	ModelTexture modelTexture2(Loader::getLoaderInstance()->loadTexture("white.jpg"));
	TexturedModel texturedModel2(rawModel2, modelTexture2);
	
	this->lightEntity = Entity(texturedModel2, position, 0, 0, 0, 1, 0);
}


Light::~Light()
{
}
