#pragma once
#include <vector>
#include <GL/glew.h>

#include "rawModel.h"


class Loader
{
public:
	Loader();
	~Loader();

	RawModel loadToVAO(GLfloat vertices[], GLuint sizeOfVertices, GLuint indices[], GLuint sizeOfIndices);

private:
	std::vector<GLuint> pVAOvector;
	std::vector<GLuint> pVBOvector;
};

