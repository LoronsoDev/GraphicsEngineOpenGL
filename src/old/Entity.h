#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>

class Entity
{
public:
	Entity();
	glm::vec4 getPos();
	glm::vec4 getRot();
	glm::vec4 getScale();
	glm::mat4 getModelMatrix();
	void setPos(glm::vec4 pos);
	void setRot(glm::vec4 rot);
	void setScale(glm::vec4 scale);
	void setModelMatrix(glm::mat4 modelMatrix);
	void computeModelMatrix();
	virtual void step(double deltaTime)=0;
private:
	glm::vec4 pos;
	glm::vec4 rot;
	glm::vec4 escala;
	glm::mat4 modelMatrix;
};


