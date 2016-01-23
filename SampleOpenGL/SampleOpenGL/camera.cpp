#include "stdafx.h"
#include "camera.h"




camera::camera(glm::vec3 _pos, glm::vec3 _globalUp, GLfloat _yaw, GLfloat _pitch) : forward(CAM_FORWARD), camSpeed(SPEED), mouseSensitivity(SENSITIVTY), camZoom(ZOOM) {
	pos = _pos;
	globalUp = _globalUp;
	yaw = _yaw;
	pitch = _pitch;
}

camera::~camera()
{
}

glm::mat4 camera::getViewMat() {
	return glm::lookAt(pos, pos + forward, up);
}

void camera::updateCamVectors() {
	// uses Euler angles to get values of direction vector forward
	forward.x = cos(glm::radians(pitch)) *  cos(glm::radians(yaw));
	forward.y = sin(glm::radians(pitch));
	forward.z = cos(glm::radians(pitch)) *  sin(glm::radians(yaw));
	forward = glm::normalize(forward);

	//takes cross products to find perepndicular camera right and up vectors using the cross product 
	right = glm::normalize(glm::cross(globalUp, forward));
	up = glm::normalize(glm::cross(forward, right));
}




void camera::processMouseInput(GLfloat mouseDeltaX, GLfloat mouseDeltaY, bool canFlipOrientation = GL_FALSE) {
	//adjusting mouse offset by mouse sensitivity
	mouseDeltaX *= mouseSensitivity;
	mouseDeltaY *= mouseSensitivity;

	//change direction
	yaw += mouseDeltaX;
	pitch += mouseDeltaY;

	//checking if pitch is out of bounds and preventing it from doing so
	if (canFlipOrientation) {
		if (pitch> 89.9f) {
			pitch = 89.9f;
		}
		if (pitch < -89.9f) {
			pitch = -89.9f;
		}
	}
	updateCamVectors();
}

void camera::processKeyInput(Camera_Directions dir, GLfloat deltaTime) {
	GLfloat velocity = camSpeed * deltaTime;
	if (dir == FORWARD) {
		pos += forward * velocity;
	}
	if (dir == BACKWARD) {
		pos -= forward * velocity;
	}
	if (dir == RIGHT) {
		pos -= right * velocity;
	}
	if (dir == LEFT) {
		pos += right * velocity;
	}
}


