#pragma once
#include <vector>
#include <GL/glew.h>
#include <string>
#include "rawModel.h"


class Loader
{
public:
	static Loader* getLoaderInstance();
	
	~Loader();

	RawModel loadToVAO(GLfloat vertices[], GLuint sizeOfVertices, GLuint indices[], GLuint sizeOfIndicesGLfloat, GLfloat textureCoordinates[], GLint sizeofTextureCoordinates);

	GLuint loadTexture(std::string filePath);

private:
	static Loader * instance;
	Loader();

	std::vector<GLuint> pVAOVector;
	std::vector<GLuint> pVBOVector;
	std::vector<GLuint> pEBOVector;

	void storeDataInAttributeList(int attributeNumber, int coordinateSize, float data[], int sizeOfData);
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, int data[], int sizeOfData);
};

