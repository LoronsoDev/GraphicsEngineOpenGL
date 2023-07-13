#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>

#include "engine/base/InputManager.h"

class Entity
{
public:
	std::string name = "Entity";

	virtual ~Entity() = default;
	Entity();

	/* GETTERS */
	inline glm::vec3 GetPos() { return m_Pos; }
	inline glm::vec4 GetRot() { return m_Rot; }
	inline glm::vec4 GetScale() { return m_Scale; }
	inline glm::mat4 GetModelMatrix() { return m_ModelMatrix; }

	/* SETTERS */
	inline void SetPos(glm::vec3 pos) { m_Pos = pos; }
	inline void SetRot(glm::vec4 rot) { m_Rot = rot; }
	inline void SetScale(glm::vec4 scale) { m_Scale = scale; }
	inline void SetModelMatrix(glm::mat4 modelMatrix) { m_ModelMatrix = modelMatrix; }
	virtual void ComputeModelMatrix();
	virtual void Step(float deltaTime) = 0;

private:
	glm::vec3 m_Pos;
	glm::vec4 m_Rot;
	glm::vec4 m_Scale;
	glm::mat4 m_ModelMatrix;
};
