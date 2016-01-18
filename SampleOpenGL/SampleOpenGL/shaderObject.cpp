#include "stdafx.h"
#include "shaderObject.h"
#include <sstream>
#include <fstream>


std::string loadFile(std::string path) {
	std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();

	return buffer.str();
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

	const GLchar *shaderFile = loadFile(Path).c_str();
	glShaderSource(id, 1, &shaderFile, NULL);
	glCompileShader(id);

	//check for errors
	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		GLint infoLog;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLog);

		GLchar *strInfoLog = new GLchar[infoLog + 1];


		fprintf(stderr, "Compile failure in %s shader:\n%s\n", shaderType, strInfoLog);
		delete[] strInfoLog;
	}
}

shaderObject::~shaderObject()
{
	glDeleteShader(id);
}
