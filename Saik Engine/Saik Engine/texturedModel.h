#pragma once

#include <GL/glew.h>

#include "rawModel.h"
#include "modelTexture.h"

class TexturedModel
{
public:
	TexturedModel() {}
	TexturedModel(RawModel rawModel, ModelTexture modelTexture);

	RawModel getRawModel() { return mRawModel; }
	ModelTexture getModelTexture() { return mModelTexture; }

private:

	RawModel mRawModel;
	ModelTexture mModelTexture;
};

