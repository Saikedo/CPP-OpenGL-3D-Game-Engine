#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:
	Window(const int width,const int height, const char * title);
	~Window();

	GLFWwindow  * getWindow() 
	{
		return window; 
	};

	int getWindowWidth()
	{ 
		return screenWidth;
	}

	int getWindowHeight()
	{
		return screenHeight;
	}

	void setGlViewport();

private:
	GLFWwindow *window;
	int screenWidth;
	int screenHeight;
};

