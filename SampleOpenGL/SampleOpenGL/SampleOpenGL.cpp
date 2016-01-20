// SampleOpenGL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Engine.h"
#include "framework.h"
#include <iostream>

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 800;



int main()
{
	//initializing GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//initializing window
	GLFWwindow* window = glfwCreateWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "Sample OpenGL", nullptr, nullptr);
	if (window == NULL) {
		std::cout << "Failed to create GLFLW window \n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	//initalizing GLEW
	glewExperimental = GLU_TRUE;
	if ((glewInit() != GLEW_OK)) {
		std::cout << "GLEW failed to properly intialize! \n";
		return -1;
	}

	//define ViewPort
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//create Engine
	Engine engine;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		//Rendering code
		engine.draw();

		glfwSwapBuffers(window);
	}
	engine.close();
	glfwTerminate();
    return 0;
}

//checks for key input , called to GFLW by glfwSetKeyCallback(window, key_callback)
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}