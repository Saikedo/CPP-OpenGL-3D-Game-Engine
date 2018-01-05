#pragma once

#include "rawModel.h"
#include "modelTexture.h"
#include "loader.h"
class Terrain
{
public:
	Terrain(int gridX, int gridZ, ModelTexture texture);
	~Terrain();

	RawModel getRawModel() { return model; }
	ModelTexture getModelTexture() { return texture; }

private:
	const float SIZE = 400;
	const float VERTEX_COUNT = 128;

	float x;
	float z;
	RawModel model;
	ModelTexture texture;

	RawModel generateTerrain();


};

