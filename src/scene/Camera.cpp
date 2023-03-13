#include "Camera.h"

#include <engine/base/InputManager.h>

void Camera::computeProjectionMatrix(float aspectRatio)
{
	projection = glm::perspective(glm::radians(horizontalFov), aspectRatio, nearPlane, farPlane);
}

void Camera::computeViewMatrix()
{
	view = glm::lookAt(glm::vec3(GetPos()), lookAt, { 0.0f,1.0f,0.0f });
}

void CameraKeyboard::Step(float timestep)
{
	float cameraMovementSpeedMultiplier = 2;

	static float prevYaw = input->mousePosX;
	static float prevPitch = input->mousePosY;

	//mouse velocities
	float yaw = prevYaw - input->mousePosX;
	float pitch = prevPitch - input->mousePosY;

	if (GetRot().y > 3.1415f * .5f)
	{
		SetRot({GetRot().x,  3.14f * .5f, GetRot().z, 1.0f});
		pitch = 0;
	}
	if (GetRot().y < -3.1415f * .5f)
	{
		SetRot({GetRot().x,  -3.14f * .5f, GetRot().z, 1.0f });
		pitch = 0;
	}

	prevYaw = input->mousePosX;
	prevPitch = input->mousePosY;

	glm::vec4 totalRotation = { yaw, pitch, 0, 0 };

	totalRotation *= mouseSens * timestep;

	this->SetRot(GetRot() + totalRotation);

	lookAt = glm::rotate(glm::mat4(1.0f), GetRot().x, glm::vec3(0.0f, 1.f, 0.f))
	* glm::rotate(glm::mat4(1.0f), GetRot().y, glm::vec3(1.0f, 0.f, 0.f))
	* glm::vec4(radius, 1.0f);

	lookAt += glm::vec3(GetPos());

	glm::vec3 dir = glm::normalize(lookAt - glm::vec3(GetPos()));

	float finalSpeed = speed;

	if (input->GetKeyState(GLFW_KEY_LEFT_SHIFT)) finalSpeed *= cameraMovementSpeedMultiplier;
	else finalSpeed *= 1/cameraMovementSpeedMultiplier;

	if (input->GetKeyState(GLFW_KEY_A)) SetPos(GetPos() - glm::cross(dir, up) * finalSpeed);
	if (input->GetKeyState(GLFW_KEY_D)) SetPos(GetPos() + glm::cross(dir, up) * finalSpeed);
	if (input->GetKeyState(GLFW_KEY_W)) SetPos(GetPos() + dir * finalSpeed);
	if (input->GetKeyState(GLFW_KEY_S)) SetPos(GetPos() - dir * finalSpeed);

	computeViewMatrix();
}
