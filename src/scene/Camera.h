#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>
#include <scene/Entity.h>
#include <engine/base/Kernel.h>

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
	glm::mat4 view, projection;
	glm::vec3 up, lookAt;

public:
	Camera(ProjectionType projectionType, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt);
	glm::mat4 getProjection();
	glm::mat4 getView();
	void computeProjectionMatrix();
	void computeViewMatrix();

	virtual void Step(float timestep) = 0;
};

class CameraKeyboard : public Camera
{
public:
	float velocity = 2.5f;

public:
	void Step(float timestep) override;
};