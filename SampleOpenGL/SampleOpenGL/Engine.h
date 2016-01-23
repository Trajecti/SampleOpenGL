#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include  <memory>
#include "shaderProgram.h"
#include "camera.h"
#include "InputCallBackWrapper.h"

struct input {
	//keeps track of keys pressed 
	bool keys[1024];
	int lastMouseX, lastMouseY;
	bool mouseClickedOnce;
};

class Engine: public InputCallBackWrapper
{
public:
	Engine();
	void init();
	void set_dim(GLuint width, GLuint height);
	void initBuffers();
	void draw();
	~Engine();
	void close();

	//checks for key input , called to GFLW by glfwSetKeyCallback(window, key_callback)
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void key_input();
	void mouse_callback(GLFWwindow* window, double mousex, double mousey);

private:
	std::unique_ptr<shaderProgram> program;
	std::string vertexTexLoc;
	GLuint width, height;
	GLuint vao, vbo, ebo;
	GLuint tex1, tex2;

	input inputData;


	GLfloat deltaTime, lastFrame;
	std::unique_ptr<camera> cam;
	//model matrix transforms model to world space
	//view matrix from world space to camera space
	//projection matrix from view space to clipspace
	glm::mat4 model,view,projection;
};

