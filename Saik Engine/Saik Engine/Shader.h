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

	void getAllUniformLocations();


	// Uses the current shader
	void start()
	{
		glUseProgram(mShaderProgramID);
	}

	void stop()
	{
		glUseProgram(0);
	}

	GLuint getShaderID() {
		return mShaderProgramID;
	}


	void setBool(GLuint location, bool value) const
	{
		glUniform1i(location, (int)value);
	}
	void setInt(GLuint location, int value) const
	{
		glUniform1i(location, value);
	}
	void setFloat(GLuint location, float value) const
	{
		glUniform1f(location, value);
	}

private:
	GLuint mShaderProgramID;
};