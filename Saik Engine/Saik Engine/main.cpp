#include <iostream>
#include <string>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "Shader.h"
#include "loader.h"
#include "rawModel.h"


const GLint WINDOW_WIDTH = 1280;
const GLint WINDOW_HEIGHT = 720;
const char * WINDOW_TITLE = "Saik Engine";


void processInput(GLFWwindow *window);



int main()
{
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);


	window.setGlViewport();


	glewExperimental = GL_TRUE; // Let`s GLEW to know to use modern stuff

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;

		return EXIT_FAILURE;
	}



	Loader loader;

	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	GLuint indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};



	RawModel rawModel = loader.loadToVAO(vertices, sizeof(vertices), indices, sizeof(indices));

	


	glBindVertexArray(rawModel.getVaoID());
	//set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0); // Set vertex attr pointers
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	Shader shader("vertexShader.vert", "fragmentShader.frag");

	while (!glfwWindowShouldClose(window.getWindow()))
	{
		glClearColor(0.5f, 0.2f, 0.4f, 1.0f); // background color
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window.getWindow());

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enables wireframe mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Disables wireframe mode

		shader.start();
		glBindVertexArray(rawModel.getVaoID());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		std::cout << "SPACE " << std::endl;
	}

}

