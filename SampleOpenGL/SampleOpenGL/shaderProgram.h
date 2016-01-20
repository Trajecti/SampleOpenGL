#pragma once
#include <GL\glew.h>
#include <vector>
#include <map>
#include <string>

class shaderProgram
{
public:
	GLuint id;
	int shaderCount;
	std::map<std::string, GLuint> shaderVar;

	shaderProgram& operator=(shaderProgram other);
	shaderProgram();
	shaderProgram(std::string vPath, std::string fPath);
	shaderProgram(std::vector<GLuint> shaders);
	~shaderProgram();

	void use();

	void addShader(GLuint shader);
	void addShader(std::string filePath,std::string type);

	void removeShaders();
	void linkProgram();
	void compileShaders(std::vector<GLuint> shaders);

	void addAttrib(std::string attr);
	void addUniform(std::string unif);
private:
	std::vector<GLuint> currentShaders;
};

