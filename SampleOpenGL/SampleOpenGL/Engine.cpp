#include "stdafx.h"
#include "Engine.h"

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f, // Left  
	0.5f, -0.5f, 0.0f, // Right 
	0.0f,  0.5f, 0.0f  // Top   
};


std::string vPath = "data/pos.vert";
std::string fPath = "data/pos1.frag";

void Engine::initBuffers() {
	

	//create buffers
	glGenVertexArrays(1, &vao);

	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
}

//Initializes engine
Engine::Engine()
{
	//create program with vertex and fragment shaders

	program.reset(new shaderProgram(vPath,fPath));
	initBuffers();
}

//renders vertex data to screen
void Engine::draw() {

	//clear with black screen
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	program->use();
	
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);
	glBindVertexArray(0);

}

Engine::~Engine()
{
}

void Engine::close()
{
	glDeleteProgram(program->id);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}
