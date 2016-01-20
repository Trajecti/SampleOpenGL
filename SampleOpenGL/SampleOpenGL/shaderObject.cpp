#include "stdafx.h"
#include "shaderObject.h"
#include <sstream>
#include <iostream>
#include <fstream>



std::string loadFile(std::string path) {
	std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string temp = buffer.str();
	return temp;
};


shaderObject::shaderObject(std::string Path, GLenum eShaderType){
	//create,load and compile shader
	id = glCreateShader(eShaderType);


	shaderType = NULL;
	switch (eShaderType) {
	case GL_VERTEX_SHADER: shaderType = "vertex"; break;
	case GL_GEOMETRY_SHADER: shaderType = "geometry"; break;
	case GL_FRAGMENT_SHADER: shaderType = "fragment"; break;
	}

	std::string shaderFile = loadFile(Path) + '\n';
	const char *strData = shaderFile.c_str();
	glShaderSource(id, 1, &strData, NULL);
	glCompileShader(id);

	GLint bufflen;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &bufflen);
	if (bufflen > 1)
	{
		GLchar* log_string = new GLchar[bufflen + 1];
		glGetShaderInfoLog(id, bufflen, 0, log_string);
		fprintf(stderr, "Compile failure in %s shader:\n%s\n", shaderType, log_string);

		delete log_string;
	}
	//check for errors
	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		GLint infoLog;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLog);

		GLchar *strInfoLog = new GLchar[infoLog + 1];


		fprintf(stderr, "Compile failure in %s shader:\n%s\n", shaderType, strInfoLog);
		delete[] strInfoLog;
	}
}

shaderObject::~shaderObject()
{
}
