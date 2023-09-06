#pragma once
#include <scene/Light.h>

class OrbitalLight : public Light
{
private:
	float angle = 0.f;
	glm::vec3 radius = glm::vec3(0,1,0);
public:
	glm::mat4 transform = glm::mat4(1);
	float speed = 200.f;

	OrbitalLight(LightType type, float speed, glm::vec3 position)
		: Light(type),
		  speed(speed)
	{
		this->position = position;
		radius = position;
		manualControl = false;
	}

	void step(double timeStep) override;
};