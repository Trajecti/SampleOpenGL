#include "stdafx.h"
#include "Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"





GLfloat vertices[] = {
	// Positions          // Colors           // Texture Coords
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
};

GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
};

std::string vPath = "data/pos.vert";
std::string fPath = "data/pos1.frag";
std::string t0Path = "data/container.jpg";
std::string t1Path = "data/awesome_face.jpg";

void Engine::initBuffers() {

	stbi_set_flip_vertically_on_load(true);

	//create buffers
	glGenVertexArrays(1, &vao);

	glGenBuffers(1, &ebo);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//pos attribute
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//texture attribute

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//gen texture
	glGenTextures(1, &tex1);
	glBindTexture(GL_TEXTURE_2D, tex1);
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load image 1
	int tWidth, tHeight,rgb;
	unsigned char *image = stbi_load(t0Path.c_str(), &tWidth, &tHeight, &rgb, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//gen texture2
	glGenTextures(1, &tex2);
	glBindTexture(GL_TEXTURE_2D, tex2);
	//Set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// now texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load image
	image = stbi_load(t1Path.c_str(), &tWidth, &tHeight, &rgb, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//Initializes engine
Engine::Engine()
{
	//create program with vertex and fragment shaders
	program.reset(new shaderProgram(vPath,fPath));

	program->addUniform("myTexture1");
	program->addUniform("myTexture2");

	initBuffers();
}

//renders vertex data to screen
void Engine::draw() {

	//clear with black screen
	glClearColor(0.0, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//using program
	program->use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex1);
	glUniform1i(program->shaderVar["myTexture1"], 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex2);
	glUniform1i(program->shaderVar["myTexture2"], 1);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
	glUseProgram(0);
	glBindVertexArray(0);

}

Engine::~Engine()
{
}

void Engine::close()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteProgram(program->id);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}
