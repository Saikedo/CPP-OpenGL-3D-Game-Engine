#pragma once


#include <GL\glew.h>
#include <string>
#include <iostream>

class ModelTexture
{
public:
	ModelTexture() {};
	ModelTexture(std::string fileName);
	~ModelTexture();

	GLuint getTextureID() { return mTextureID; }

private:
	GLuint mTextureID;
};

