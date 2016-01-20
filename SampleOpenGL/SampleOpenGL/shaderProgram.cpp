#include "stdafx.h"
#include "shaderProgram.h"
#include "shaderObject.h"

//plain constructor
shaderProgram::shaderProgram(){
	id = glCreateProgram();
	shaderCount = 0;
}

// Shaders


//constructor taking vertex and fragment file paths directly
shaderProgram::shaderProgram(std::string vPath, std::string fPath){
	id = glCreateProgram();
	shaderCount = 0;

	addShader(vPath,"vertex");
	addShader(fPath,"fragment");

	linkProgram();
	removeShaders();
}

// constructor that adds many shaders at once
shaderProgram::shaderProgram(std::vector<GLuint> shaders){
	id = glCreateProgram();
	shaderCount = 0;
	compileShaders(shaders);
}

//compiles many shaders at once
void shaderProgram::compileShaders(std::vector<GLuint> shaders){
	for (auto i : shaders) {
		addShader(i);
	}

	linkProgram();
	use();
	removeShaders();
}

shaderProgram::~shaderProgram(){
	glDeleteProgram(id);
}

void shaderProgram::use(){
	{ glUseProgram(this->id); }
}

void shaderProgram::addShader(GLuint shader){
	glAttachShader(id, shader);
	currentShaders.push_back(shader);
	shaderCount++;
}

//Alternate constructor that compiles shader itself
void shaderProgram::addShader(std::string filePath, std::string type) {

	//setting type to a null variable
	GLenum gType = 0;
	if (type.find("vertex")!= std::string::npos) {
		gType = GL_VERTEX_SHADER;
	}
	else if (type.find("fragment") != std::string::npos) {
		gType = GL_FRAGMENT_SHADER;
	}
	else if (type.find("geometry") != std::string::npos) {
		gType = GL_GEOMETRY_SHADER;
	}

	//If valid type
	if (gType != 0) {
		GLuint temp = shaderObject(filePath, gType).id;
		glAttachShader(id,temp);
		currentShaders.push_back(temp);
		shaderCount++;
	}
	else {
		fprintf(stderr, "Engine Error: Invalid Shader type specified!");
	}
}

void shaderProgram::removeShaders() {
	for (auto i : currentShaders) {
		glDetachShader(id, i);
		glDeleteShader(i);
		shaderCount--;
	}
	currentShaders.clear();
}

void shaderProgram::addAttrib(std::string attrib) {
	shaderVar.insert(std::make_pair(attrib,glGetAttribLocation(id, attrib.c_str())));
}

void shaderProgram::addUniform(std::string unif){
	shaderVar.insert(std::make_pair(unif, glGetUniformLocation(id, unif.c_str())));
}

void shaderProgram::linkProgram() {
	if (shaderCount != 0) {
		glLinkProgram(id);

		GLint status;
		glGetProgramiv(id, GL_LINK_STATUS, &status);
		// check if compiling had errors
		if (status == GL_FALSE) {
			GLint infoLogLen;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLen);

			GLchar *infoLog = new GLchar[infoLogLen + 1];
			glGetProgramInfoLog(id, infoLogLen, NULL, infoLog);
			fprintf(stderr, "Linker failure: %s\n", infoLog);
			delete[] infoLog;
		}

		glValidateProgram(id);
		glGetProgramiv(id, GL_VALIDATE_STATUS, &status);
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

shaderProgram& shaderProgram::operator=(shaderProgram other)
{
	using std::swap;
	swap(id, other.id);
	// repeat for other member variables;
	return *this;
}