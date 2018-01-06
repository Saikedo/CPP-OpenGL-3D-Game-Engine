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


RawModel Loader::loadToVAO(GLfloat vertices[], GLuint sizeOfVertices, GLuint indices[], GLuint sizeOfIndices,
	GLfloat textureCoordinates[], GLint sizeofTextureCoordinates)
{
	// Generate Vertex Attribute Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &VBO); //Generates buffer on  GPU and returns the I
						   //copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binds the Buffer type to provided buffer ID
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW); //Copies data to GPU
																			 // position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	GLuint VBO2;
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeofTextureCoordinates, textureCoordinates, GL_STATIC_DRAW); //Copies data to GPU
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

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