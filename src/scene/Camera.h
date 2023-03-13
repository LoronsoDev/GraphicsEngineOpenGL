#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>
#include <scene/Entity.h>

#include "engine/base/InputManager.h"

class Camera : public Entity
{
public:
	enum ProjectionType
	{
		PERSPECTIVE,
		ORTOGONAL,
		UNDEFINED
	};

public:
	float horizontalFov = 90.0f;
	float nearPlane = 0.01f;
	float farPlane = 100.0f;

	glm::mat4 view, projection;
	glm::vec3 up;
	glm::vec3 lookAt; //point in space to look at.

	ProjectionType projectionType;

	glm::vec3 radius;

public:
	Camera(ProjectionType projectionType, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt)
	{
		SetPos(glm::vec4(1));
		this->projectionType = projectionType;
		this->up = up;
		this->lookAt = lookAt;

		radius = lookAt - position;
	};

	inline glm::mat4 getProjection() { return projection; }
	inline glm::mat4 getView() { return view; }
	void computeProjectionMatrix(float aspectRatio);
	void computeViewMatrix();

	virtual void Step(float timestep) = 0;
};

class CameraKeyboard : public Camera
{
private:
	engine::InputManager* input = nullptr;

public:
	CameraKeyboard(ProjectionType projectionType, glm::vec3 position, glm::vec3 up,
		glm::vec3 lookAt, engine::InputManager * inputManager,
		float speed = 2.5f, float mouseSens = 1.f) :
	Camera(projectionType, position, up, lookAt),
	input(inputManager),
	speed(speed),
	mouseSens(mouseSens)
	{
		this->SetPos(position);
	};

	float speed = 2.5f;
	float mouseSens = 0.1f;

public:
	void Step(float timestep) override;
};