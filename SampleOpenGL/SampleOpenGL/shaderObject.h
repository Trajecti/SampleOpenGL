#pragma once
#include <GL\glew.h>
#include <string>

class shaderObject
{
public:

	GLuint id;
	GLchar* shaderType;
	shaderObject(std::string vertexPath,GLenum shaderType);
	~shaderObject();
};

std::string loadFile(std::string path);