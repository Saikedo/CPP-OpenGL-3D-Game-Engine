#include "loader.h"
#include <iostream>

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