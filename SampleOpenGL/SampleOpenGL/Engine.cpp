#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "Engine.h"

#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

/* GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
};
*/

std::string vPath = "data/pos.vert";
std::string fPath = "data/pos1.frag";
std::string t0Path = "data/container.jpg";
std::string t1Path = "data/awesome_face.jpg";

void Engine::initBuffers() {

	stbi_set_flip_vertically_on_load(true);

	//create buffers
	glGenVertexArrays(1, &vao);

	//glGenBuffers(1, &ebo);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//pos attribute
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//texture attribute

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
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
Engine::Engine(){
	//create program with vertex and fragment shaders
	program.reset(new shaderProgram(vPath, fPath));
	cam.reset(new camera());
	inputData.mouseClickedOnce = true;
}

void Engine::init(){

	glEnable(GL_DEPTH_TEST);

	GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
	GLfloat lastFrame = 0.0f;   //time of last frame

	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	program->addUniform("myTexture1");
	program->addUniform("myTexture2");
	program->addUniform("model");
	program->addUniform("view");
	program->addUniform("projection");

	initBuffers();
}

void Engine::set_dim(GLuint widthx, GLuint heightx)
{
	width = widthx;
	height = heightx;
}

//renders vertex data to screen
void Engine::draw() {

	//clear with black screen
	glClearColor(0.0, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	key_input();

	//using program
	program->use();


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex1);
	glUniform1i(program->shaderVar["myTexture1"], 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex2);
	glUniform1i(program->shaderVar["myTexture2"], 1);

	//set matrix
	model = glm::rotate(model, glm::radians(0.05f), glm::vec3(0.5f, 1.0f, 0.0f));
	view = cam->getViewMat();
	glUniformMatrix4fv(program->shaderVar["model"], 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(program->shaderVar["view"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(program->shaderVar["projection"], 1, GL_FALSE, glm::value_ptr(projection));
	
	glBindVertexArray(vao);
	for (GLuint i = 0; i < 10; i++)
	{
		glm::mat4 modeli;
		modeli = glm::translate(modeli , cubePositions[i]);
		GLfloat angle = glm::radians(20.0f) * i;
		if (i % 3 == 0)  // Every 3rd iteration (including the first) we set the angle using GLFW's time function.
			angle = glfwGetTime() * glm::radians(25.0f);
		model = glm::rotate(modeli, angle, glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(program->shaderVar["model"], 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
	glDrawArrays(GL_TRIANGLES,0,36);
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

//checks for key input , called to GFLW by glfwSetKeyCallback(window, key_callback)
void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (inputData.keys[GLFW_KEY_ESCAPE]) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (action == GLFW_PRESS) {
		inputData.keys[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		inputData.keys[key] = false;
	}
}

void Engine::key_input(){
	if (inputData.keys[GLFW_KEY_W]) {
		cam->processKeyInput(FORWARD, deltaTime);
	}
	if (inputData.keys[GLFW_KEY_A]) {
		cam->processKeyInput(LEFT, deltaTime);
	}
	if (inputData.keys[GLFW_KEY_S]) {
		cam->processKeyInput(BACKWARD, deltaTime);
	}
	if (inputData.keys[GLFW_KEY_D]) {
		cam->processKeyInput(RIGHT, deltaTime);
	}
}

void Engine::mouse_callback(GLFWwindow * window, double mousex, double mousey){
	//if first record of mouse coords  initialize properly
	if (inputData.mouseClickedOnce) {
		inputData.lastMouseX= mousex;
		inputData.lastMouseY= mousey;
		inputData.mouseClickedOnce = false;
	}

	//get offset
	GLfloat xOffset = mousex - inputData.lastMouseX;
	GLfloat yOffset = inputData.lastMouseY - mousey;
	inputData.lastMouseX = mousex;
	inputData.lastMouseY = mousey;

	//process input
	cam->processMouseInput(xOffset, yOffset,false);

}
