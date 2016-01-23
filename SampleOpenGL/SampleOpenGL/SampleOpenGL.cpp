// SampleOpenGL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Engine.h"
#include "framework.h"
#include <iostream>

const int SCREEN_HEIGHT = 768;
const int SCREEN_WIDTH =1024;



int main()
{
	//initializing GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//initializing window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sample OpenGL", nullptr, nullptr);
	if (window == NULL) {
		std::cout << "Failed to create GLFLW window \n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	engine.set_dim(SCREEN_WIDTH, SCREEN_HEIGHT);
	engine.init();
	glfwSetKeyCallback(window,InputCallBackWrapper::key_callback_dispatch);
	glfwSetCursorPosCallback(window, InputCallBackWrapper::mouse_callback_dispatch);
	while (!glfwWindowShouldClose(window)) {
		engine.setEventHandling();
		glfwPollEvents();
		//Rendering code
		engine.draw();
		glfwSwapBuffers(window);
	}
	engine.close();
	glfwTerminate();
    return 0;
}

