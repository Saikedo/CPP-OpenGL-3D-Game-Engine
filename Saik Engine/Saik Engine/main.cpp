#pragma once
#include <iostream>
#include <string>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.h"
#include "Shader.h"
#include "loader.h"
#include "rawModel.h"
#include "modelTexture.h"
#include "texturedModel.h"
#include "camera.h"
#include "terrain.h"

const GLint WINDOW_WIDTH = 800;
const GLint WINDOW_HEIGHT = 600;
const char * WINDOW_TITLE = "Saik Engine";


void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// TODO Delete VBO EBO ABO`s from Loader
// TODO Make sure camera instance is deleted

// Delete this when done with cubes
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = 400, lastY = 300;
bool firstMouseMovement = true;



float FOV = 45.0;

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


	//  Hide the cursor and capture it.
	glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader shader("vertexShader.vert", "fragmentShader.frag");
	shader.getAllUniformLocations();

	Shader terrainShader("terrainVertexShader.vert", "terrainFragmentShader.frag");
	terrainShader.getAllUniformLocations();

	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f,  
		-0.5f, -0.5f, -0.5f, 

		-0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f,  
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f, 

		-0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		-0.5f, -0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f, 

		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,  
		0.5f, -0.5f, -0.5f,  
		0.5f, -0.5f,  0.5f,  
		0.5f,  0.5f,  0.5f,  

		-0.5f, -0.5f, -0.5f,  
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f,  
		0.5f, -0.5f,  0.5f,  
		-0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f, -0.5f, 

		-0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f, 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};



	GLfloat textureCoordinates[] = {
		 0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		 0.0f, 0.0f,
		1.0f, 0.0f,
		 1.0f, 1.0f,
		1.0f, 1.0f,
		 0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		 1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		 0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};


	Terrain terrain(0, 0, ModelTexture("db.jpg"));

	
	RawModel rawModel = Loader::getLoaderInstance()->loadToVAO(vertices, sizeof(vertices), indices, sizeof(indices), textureCoordinates, sizeof(textureCoordinates));
	ModelTexture modelTexture("container.jpg");
	TexturedModel texturedModel(rawModel, modelTexture);


	///////////////////////////////////////////////////////////////////////////////////////
	
	


	shader.start();
	glUniform1i(glGetUniformLocation(shader.getShaderID(), "texture1"), 0);
	shader.stop();

	terrainShader.start();
	glUniform1i(glGetUniformLocation(terrainShader.getShaderID(), "texture1"), 0);
	terrainShader.stop();
	///////////////////////////////////////////////////////////////////////////////////////

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// Register mouse movement listener
	glfwSetCursorPosCallback(window.getWindow(), mouse_callback);
	glfwSetScrollCallback(window.getWindow(), scroll_callback);

	while (!glfwWindowShouldClose(window.getWindow()))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window.getWindow());
			

		glEnable(GL_DEPTH_TEST);

		glClearColor(0.5f, 0.2f, 0.4f, 1.0f); // background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enables wireframe mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Disables wireframe mode


		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturedModel.getModelTexture().getTextureID());
	
		Camera::getCameraInstance()->update();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(FOV), float (window.getWindowWidth()) / (float) (window.getWindowHeight()), 0.1f, 1000.0f);

		shader.start();

		

		int viewLoc = glGetUniformLocation(shader.getShaderID(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(Camera::getCameraInstance()->getCameraView()));

		int projectionLoc = glGetUniformLocation(shader.getShaderID(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));




		glBindVertexArray(texturedModel.getRawModel().getVaoID());

		//glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			int modelLoc = glGetUniformLocation(shader.getShaderID(), "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glBindVertexArray(0);
		shader.stop();
		

		terrainShader.start();

		
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(Camera::getCameraInstance()->getCameraView()));


		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		int modelLoc = glGetUniformLocation(shader.getShaderID(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, terrain.getModelTexture().getTextureID());
		glBindVertexArray(terrain.getRawModel().getVaoID());
		glDrawElements(GL_TRIANGLES, terrain.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		terrainShader.stop();



		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());

		// Checks erros in shaders
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cout << "main: fragmentError: " << err << std::endl;
		}
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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Camera::getCameraInstance()->move(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Camera::getCameraInstance()->move(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Camera::getCameraInstance()->move(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Camera::getCameraInstance()->move(RIGHT, deltaTime);
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Camera::getCameraInstance()->move(UP, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	//	Camera::getCameraInstance()->move(DOWN, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouseMovement)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouseMovement = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	Camera::getCameraInstance()->changeYaw(xoffset);
	Camera::getCameraInstance()->changePitch(yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (FOV >= 1.0f && FOV <= 45.0f)
		FOV -= yoffset;
	if (FOV <= 1.0f)
		FOV = 1.0f;
	if (FOV >= 45.0f)
		FOV = 45.0f;
}