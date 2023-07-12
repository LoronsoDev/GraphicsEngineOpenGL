#pragma once

#define GLAD_ONLY_HEADERS
#include <Engine_Core.h>

#include <scene/Object.h>

class Light
{
public:
	virtual ~Light() = default;

	enum LightType
	{
		DIRECTIONAL,
		POINT,
		SPOT,
		AREA
	};

	std::string name = "Light";

	bool manualControl = true;

	Object* sceneVisualizer = nullptr;	//Keep at null if you don't want to represent it in the scene.
	LightType lightType;
	float intensity = 1.0f;
	float linearAttenuation = 0.7;			//	Linear set for a distance of +-50
	float quadraticAttenuation = 1.8;		//	Quadratic set for a distance of +-50
	glm::vec3 specularColor = { 1,1,1 };
	glm::vec3 color = {1,1,1};
	glm::vec3 position = {0,0,0};
	glm::vec3 direction = {1,1,1};

	Light(LightType type) { lightType = type;}

public:
	inline void setType(LightType type) { lightType = type; }
	inline LightType getType() { return lightType; }
	inline const glm::vec3& getColor() const { return color; }
	inline void setColor(const glm::vec3& color) { this->color = color; }
	virtual void step(double timeStep);

	inline float getLinearAttenuation() const { return linearAttenuation; }
	void setLinearAttenuation(float att) { linearAttenuation = att; }
};

