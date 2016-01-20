#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include  <memory>
#include "shaderProgram.h"

class Engine
{
public:
	Engine();
	void initBuffers();
	void draw();
	~Engine();
	void close();
private:
	std::unique_ptr<shaderProgram> program;
	GLuint vao;
	GLuint vbo;
};

