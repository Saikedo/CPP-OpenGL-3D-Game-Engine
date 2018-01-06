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

	static Window* getWindowInstance() { return instance; }

private:
	static Window *instance;
	GLFWwindow *window;
	int screenWidth;
	int screenHeight;
};

