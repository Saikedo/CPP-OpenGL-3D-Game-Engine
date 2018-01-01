#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
	// Constructor generates the shader on the fly
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);


	// Uses the current shader
	void start()
	{
		glUseProgram(mShaderProgram);
	}

	void stop()
	{
		glUseProgram(0);
	}

private:
	GLuint mShaderProgram;
};