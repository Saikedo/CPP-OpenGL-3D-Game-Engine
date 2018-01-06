#pragma once


#include <GL\glew.h>
#include <string>
#include <iostream>

class ModelTexture
{
public:
	ModelTexture() {};

	ModelTexture(int textureID) { this->mTextureID = textureID; };

	GLuint getTextureID() { return mTextureID; }

private:
	GLuint mTextureID;
};

