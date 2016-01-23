#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//Default camera vectors
const static glm::vec3 CAM_POS = glm::vec3(0.0f, 0.0f, 0.0f);
const static glm::vec3 GLOBAL_UP = glm::vec3(0.0f, 1.0f, 0.0f);
const static glm::vec3 CAM_FORWARD = glm::vec3(0.0f, 0.0f, -1.0f);

//Default cam settings and Euler angles
const static GLfloat YAW = -90.0f;
const static GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;


//set of possible camera directions
enum Camera_Directions {
	FORWARD = GLFW_KEY_W,
	BACKWARD = GLFW_KEY_S,
	LEFT = GLFW_KEY_A,
	RIGHT = GLFW_KEY_D
};

//Camera class that utilizes Euler angles for rotation
class camera
{
public:
	//Camera vectors:
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 globalUp;

	//Euler angles:
	GLfloat pitch;
	GLfloat yaw;

	//Input options:
	GLfloat camSpeed;
	GLfloat mouseSensitivity;
	GLfloat camZoom;

	//camera constructor with vectors
	camera(glm::vec3 _pos = CAM_POS, glm::vec3 _globalUp = GLOBAL_UP, GLfloat _yaw = YAW, GLfloat _pitch = PITCH);

	//camera constructor with scalars
	~camera();

	//get view matrix
	glm::mat4 getViewMat();

	//process input method
	void processMouseInput(GLfloat mouseDeltaX, GLfloat mouseDeltaY, bool canFlipOrientation);
	void processKeyInput(Camera_Directions dir, GLfloat deltaTime);
private:
	//update cam vectors
	void updateCamVectors();
};

