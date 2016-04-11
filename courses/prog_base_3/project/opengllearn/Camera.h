#pragma once
#include "MainHeaders.h"
#include "Keyboard.h"
extern Keyboard * keyboard;
#define TURNSTEP 0.002f
#define MOVESTEP 0.008f
class Camera
{
private:
	glm::vec3 mPosition;
	glm::quat mOrientation;

public:
	void move()
	{
		if (keyboard->isKeyPressed('w'))
			moveForward(MOVESTEP);
		if (keyboard->isKeyPressed('s'))
			moveForward(-MOVESTEP);
		if (keyboard->isKeyPressed('d'))
			moveLeft(-MOVESTEP);
		if (keyboard->isKeyPressed('a'))
			moveLeft(MOVESTEP);
		if (keyboard->isKeyPressed(328)) // NUMPAD
			pitch(-TURNSTEP);
		if (keyboard->isKeyPressed(322))
			pitch(+TURNSTEP);
		if (keyboard->isKeyPressed(324))
			yaw(-TURNSTEP);
		if (keyboard->isKeyPressed(326))
			yaw(+TURNSTEP);
		glm::normalize(mOrientation);
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
		glm::quat q = glm::angleAxis(turnRadians, mOrientation * glm::vec3(0.0f, 1.0f, 0.0f));
		rotate(q);
	}

	void rotate(float angleRadians, const glm::vec3& axis) {
		glm::quat q = glm::angleAxis(angleRadians, axis);
		rotate(q);
	}

	void rotate(const glm::quat& rotation) {
		mOrientation = rotation * mOrientation;
	}

	glm::vec3 getForward() const {
		return glm::conjugate(mOrientation) * glm::vec3(0.0f, 0.0f, -1.0f);
	}

	glm::vec3 getLeft() const {
		return glm::conjugate(mOrientation) * glm::vec3(-1.0, 0.0f, 0.0f);
	}

	glm::vec3 getUp() const {
		return glm::conjugate(mOrientation) * glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void moveForward(float movement) {
		mPosition += getForward() * movement;
	}

	void moveLeft(float movement) {
		mPosition += getLeft() * movement;
	}

	void moveUp(float movement) {
		mPosition += getUp() * movement;
	}

	glm::mat4 getViewMatrix() const {
		glm::mat4 viewMatrix = glm::mat4_cast(mOrientation);
		viewMatrix = glm::translate(viewMatrix, -mPosition);
		return viewMatrix;
	}
};