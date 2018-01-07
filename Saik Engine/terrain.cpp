#include "terrain.h"



Terrain::Terrain(int gridX, int gridZ, ModelTexture texture, float specularStrength)
{
	this->texture = texture;
	x = gridX * SIZE;
	z = gridZ  * SIZE;
	this->specularStrength = specularStrength;
	model = generateTerrain();
}


Terrain::~Terrain()
{
}


RawModel Terrain::generateTerrain()
{
	int count = VERTEX_COUNT * VERTEX_COUNT;
	float *vertices = new float[count * 3];
	float *normals = new float[count * 3];
	float *textureCoordinates = new float[count * 2];
	GLuint *indices = new  GLuint[6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1)];

	int vertexPointer = 0;
	for (int i = 0;i<VERTEX_COUNT;i++) {
		for (int j = 0;j<VERTEX_COUNT;j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;

			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			
			textureCoordinates[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoordinates[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (int gz = 0;gz<VERTEX_COUNT - 1;gz++) {
		for (int gx = 0;gx<VERTEX_COUNT - 1;gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	return Loader::getLoaderInstance()->loadToVAO(vertices, sizeof(float) * (count * 3), indices, sizeof(int) * (6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1)),
		normals, sizeof(normals) * (count * 3), textureCoordinates, sizeof(float) * (count * 2));
}