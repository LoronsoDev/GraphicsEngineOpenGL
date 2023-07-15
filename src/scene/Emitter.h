#pragma once

#include <scene/Particle.h>
#include <scene/Entity.h>

class Emitter : public Entity
{
private:
	float particleAccum = 0.f;
	float emissionRate = 1.f;
	bool autoFade = false;
	std::string mshFile = "";

	glm::vec2 spinVelRange = {0.f, 1.f};
	glm::vec3 velRange[2] = {glm::vec3(1.f), glm::vec3(1.5f)};
	glm::vec2 rateRange = {5.f, 10.f};
	glm::vec2 scaleRange = {1.f, 1.f};
	glm::vec2 lifetimeRange = {1.f, 1.2f};
	glm::vec4 colorRange[2] = {glm::vec4(1.f), glm::vec4(1.f)};

	std::list<Particle*> particleList;

	bool emitting = false;


public:
	Emitter(const char* mshFile, float emissionRate, bool autoFade);
	virtual void Step(float deltaTime) override;
	void setRateRange(float min, float max);
	void setVelocityRange(const glm::vec3& min,
		const glm::vec3& max);
	void setSpinVelocityRange(float min, float max);
	void setScaleRange(float min, float max);
	void setLifetimeRange(float min, float max);
	void setColorRange(const glm::vec4& min, const glm::vec4& max);
	void emit(bool enable);
	bool isEmitting();
public:
	std::list<Particle*>* getParticleList();
};
