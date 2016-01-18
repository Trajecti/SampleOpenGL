#include "stdafx.h"
#include "shaderProgram.h"


shaderProgram::shaderProgram(){
	id = glCreateProgram();
	shaderCount = 0;
}

// other constructor that adds many shaders at once
shaderProgram::shaderProgram(std::vector<GLuint> shaders){
	id = glCreateProgram();

	for (auto i : shaders) {
		glAttachShader(id, i);
	}

	linkProgram();
}

shaderProgram::~shaderProgram(){
	glDeleteProgram(id);
}

void shaderProgram::use(){
	{ glUseProgram(this->id); }
}

void shaderProgram::addShader(GLuint shader){
	glAttachShader(id, shader);
}

void shaderProgram::removeShader(GLuint shader) {
	glDetachShader(id,shader);
	glDeleteShader(shader);
}

void shaderProgram::addAttrib(std::string attrib) {
	glGetAttribLocation(id, attrib.c_str());
}

void shaderProgram::addUniform(std::string unif){
	glGetUniformLocation(id, unif.c_str());
}

void shaderProgram::linkProgram() {
	if (shaderCount != 0) {
		glLinkProgram(id);

		GLint status;
		glGetProgramiv(id, GL_COMPILE_STATUS, &status);
		// check if compiling had errors
		if (status == GL_FALSE) {
			GLint infoLogLen;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLen);

			GLchar *infoLog = new GLchar[infoLogLen + 1];
			glGetProgramInfoLog(id, infoLogLen, NULL, infoLog);
			fprintf(stderr, "Linker failure: %s\n", infoLog);
			delete[] infoLog;
		}
	}
}