#pragma once
#include "MainHeaders.h"
#include "Keyboard.h"
#include "Window.h"
extern Keyboard * keyboard;
#define TURNSTEP 2.0f
#define MOVESTEP 1.0f
class Camera
{
private:
	glm::vec3 position;
	glm::quat orientation;

public:
	void move()
	{
		if (keyboard->isKeyPressed('w'))
			moveForward(MOVESTEP * Window::getDeltaTime());
		if (keyboard->isKeyPressed('s'))
			moveForward(-MOVESTEP* Window::getDeltaTime());
		if (keyboard->isKeyPressed('d'))
			moveLeft(-MOVESTEP * Window::getDeltaTime());
		if (keyboard->isKeyPressed('a'))
			moveLeft(MOVESTEP * Window::getDeltaTime());
		if (keyboard->isKeyPressed(328)) // NUMPAD
			pitch(-TURNSTEP * Window::getDeltaTime());
		if (keyboard->isKeyPressed(322))
			pitch(+TURNSTEP * Window::getDeltaTime());
		if (keyboard->isKeyPressed(324))
			yaw(-TURNSTEP * Window::getDeltaTime());
		if (keyboard->isKeyPressed(326))
			yaw(+TURNSTEP * Window::getDeltaTime());
		glm::normalize(orientation);
	}
	glm::fvec3 getPosition()
	{
		return this->position;
	}
	void setPosition(glm::fvec3 pos)
	{
		position = pos;
	}
	void pitch(float pitchRadians) {
		rotate(pitchRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	}

	void yaw(float yawRadians) {
		rotate(yawRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void roll(float rollRadians) {
		rotate(rollRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void turn(float turnRadians) {
		glm::quat q = glm::angleAxis(turnRadians, orientation * glm::vec3(0.0f, 1.0f, 0.0f));
		rotate(q);
	}

	void rotate(float angleRadians, const glm::vec3& axis) {
		glm::quat q = glm::angleAxis(angleRadians, axis);
		rotate(q);
	}

	void rotate(const glm::quat& rotation) {
		orientation = rotation * orientation;
	}

	glm::vec3 getForward() const {
		return glm::conjugate(orientation) * glm::vec3(0.0f, 0.0f, -1.0f);
	}

	glm::vec3 getLeft() const {
		return glm::conjugate(orientation) * glm::vec3(-1.0, 0.0f, 0.0f);
	}

	glm::vec3 getUp() const {
		return glm::conjugate(orientation) * glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void moveForward(float movement) {
		position += getForward() * movement;
	}

	void moveLeft(float movement) {
		position += getLeft() * movement;
	}

	void moveUp(float movement) {
		position += getUp() * movement;
	}
	glm::mat4 getViewMatrix() const {
		glm::mat4 viewMatrix = glm::mat4_cast(orientation);
		viewMatrix = glm::translate(viewMatrix, -position);
		return viewMatrix;
	}
};