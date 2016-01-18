#include "stdafx.h"
#include "RenderFunctions.h"
#include "shaderObject.h"
#include "shaderProgram.h"

std::string vPath = "pos.vert";
std::string fPath = "pos.frag";

GLuint vao, vbo;

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

void OpenGLinit()
{
	//create buffers
	glGenVertexArrays(1, &vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	shaderProgram program = shaderProgram();
	shaderObject vShader(vPath, GL_VERTEX_SHADER);
	shaderObject fShader(fPath, GL_FRAGMENT_SHADER);

	program.addShader(vShader.id);
	program.addShader(fShader.id);

	program.linkProgram();
	
	program.removeShader(vShader.id);
	program.removeShader(fShader.id);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	program.use();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

}
void draw() {


}