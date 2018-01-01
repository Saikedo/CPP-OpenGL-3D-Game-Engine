#pragma once

#include <GL/glew.h>


class RawModel
{
public:
	RawModel(GLuint vaoID, GLuint vertexCount)
	{
		mVaoID = vaoID;
		mVertexCount = vertexCount;
	}

	GLuint getVaoID() { return mVaoID;  }
	GLuint getVertexCount() { return mVertexCount; }

private:
	GLuint mVaoID;
	GLuint mVertexCount;
};

