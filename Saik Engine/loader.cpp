#include "loader.h"
#include <iostream>
#include "EntityRenderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Loader *Loader::instance;


Loader* Loader::getLoaderInstance()
{
	if (instance == NULL)
	{
		instance = new Loader();
	}

	return instance;
}

Loader::Loader()
{
}


Loader::~Loader()
{
	for (auto const& VAO : pVAOVector)
	{
		glDeleteVertexArrays(1, &VAO);
	}

	for (auto const& VBO : pVBOVector)
	{
		glDeleteBuffers(1, &VBO);
	}
}


RawModel Loader::loadToVAO(GLfloat vertices[], GLuint sizeOfVertices, GLuint indices[], GLuint sizeOfIndices,   GLfloat normals[], GLuint sizeOfNormals,
	GLfloat textureCoordinates[], GLint sizeofTextureCoordinates)
{
	// Generate Vertex Attribute Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	storeDataInAttributeList(0, 3, vertices, sizeOfVertices);

	storeDataInAttributeList(1, 3, normals, sizeOfNormals);

	storeDataInAttributeList(2, 2, textureCoordinates, sizeofTextureCoordinates);


	// Generate Element buffer object 
	GLuint EBO;
	glGenBuffers(1, &EBO);

	//copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

	glBindVertexArray(0); // Unbind VAO


	return RawModel(VAO, sizeOfIndices / sizeof(GLuint));
}


GLuint Loader::loadTexture(std::string fileName)
{
	GLuint textureID;
	std::string filePath = "res/textures/" + fileName;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.0f);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		textureID = -1;
		std::cout << "ModelTexture: Constructor: Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	return textureID;
}


void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, float data[], int sizeOfData)
{
	// Generate Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &VBO); //Generates buffer on  GPU and returns the I
						   //copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binds the Buffer type to provided buffer ID
	glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, GL_STATIC_DRAW); //Copies data to GPU
																			 // position attribute
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, coordinateSize * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}