#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

//call back wrapper class for GLFW input fucntions
class InputCallBackWrapper
{
public:
	//virtual functions to be used for call back
	virtual void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) = 0;
	virtual void mouse_callback(GLFWwindow *window, double xpos, double ypos) = 0;

	static InputCallBackWrapper *eventHandlingInstance;

	virtual void setEventHandling() { eventHandlingInstance = this; }

	//virtual dispatch functions
	static void mouse_callback_dispatch(GLFWwindow *window, double xpos, double ypos) {
		if (eventHandlingInstance) {
			eventHandlingInstance->mouse_callback(window, xpos, ypos);
		}
	}

	static void key_callback_dispatch(GLFWwindow *window, int key, int scancode, int action, int mods){
		if (eventHandlingInstance) {
			eventHandlingInstance->key_callback(window, key, scancode, action, mods);
		}
	}

};

