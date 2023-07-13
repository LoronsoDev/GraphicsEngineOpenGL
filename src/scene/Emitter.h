#pragma once

#include <scene/Particle.h>
#include <scene/Entity.h>

class Emitter : public Entity
{
	std::list<Particle*>* getParticleList();

public:
	Emitter(const char* mshFile, float emissionRate, bool autofade);
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
};

