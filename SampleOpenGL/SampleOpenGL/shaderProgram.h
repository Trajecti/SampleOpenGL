#pragma once
#include <GL\glew.h>
#include <vector>

class shaderProgram
{
public:
	GLuint id;
	int shaderCount;

	shaderProgram();
	shaderProgram(std::vector<GLuint> shaders);
	~shaderProgram();

	void use();
	void addShader(GLuint shader);
	void removeShader(GLuint shader);
	void linkProgram();

	void addAttrib(std::string attr);
	void addUniform(std::string unif);
};

