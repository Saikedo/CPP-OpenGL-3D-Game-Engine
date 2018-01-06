#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <glm\glm.hpp>

class Shader
{
public:
	// Constructor generates the shader on the fly
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);


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


	void setVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(mShaderProgramID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(mShaderProgramID, name.c_str()), x, y, z);
	}

private:
	GLuint mShaderProgramID;
};