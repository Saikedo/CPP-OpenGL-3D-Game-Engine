#include "loader.h"
#include <iostream>


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


RawModel Loader::loadToVAO(GLfloat vertices[], GLuint sizeOfVertices, GLuint indices[], GLuint sizeOfIndices)
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


	// Generate Element buffer object 
	GLuint EBO;
	glGenBuffers(1, &EBO);

	//copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

	glBindVertexArray(0); // Unbind VAO


	return RawModel(VAO, sizeOfVertices / sizeof(GLfloat));
}