#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window * Window::instance;

Window::Window(const int width, const int height, const char * title)
{
	instance = this;

	screenWidth = width;
	screenHeight = height;


	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // CORE_PROFILE uses new openGL stuff, COMPATIBILITY_PROFILE uses comaptibility stuff.

	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif


	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // Window resizablility

	window = glfwCreateWindow(screenWidth, screenHeight, title, nullptr, nullptr);

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight); //Size of window relative to density of the screen

	glfwMakeContextCurrent(window); //make the context of our window the main context on the current thread.

	if (window == nullptr)
	{
		std::cout << "Window: Window: Failed to create GLFW window" << std::endl;
		glfwTerminate();

		exit(EXIT_FAILURE);
	}

}


void  Window::setGlViewport()
{
	glViewport(0, 0, screenWidth, screenHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

Window::~Window()
{
}


void updateWindowSize(GLFWwindow * window)
{
	//std::cout << "BEFORE " << screenWidth << " " << screenHeight << std::endl;
//	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	//std::cout << "AFTER " << screenWidth << " " << screenHeight << std::endl;
}

//Gets called if we resize  the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	updateWindowSize(window);
	//std::cout << "DISPLAY::framebuffer_size_callback:: Window Resized to " << width << " " << height << std::endl;
	glViewport(0, 0, width, height);
}