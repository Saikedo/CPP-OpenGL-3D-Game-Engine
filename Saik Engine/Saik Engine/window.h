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

	int * getWindowDimensions() 
	{ 
		int windowDimentsions[2] = { screenWidth,  screenHeight }; 
		return windowDimentsions;
	}

	void setGlViewport();

private:
	GLFWwindow *window;
	int screenWidth;
	int screenHeight;
};

