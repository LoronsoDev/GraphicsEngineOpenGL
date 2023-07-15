#pragma once

#include <scene/Billboard.h>

class Particle : public Billboard
{
private:
	glm::vec3 vel;
	double lifeTime;
	bool autoFade;

	double timeLivedTimer;
public:
	//Constructs using Object3D loadfromfile
	Particle(
		std::string mshFile,
		const glm::vec3& vel,
		float spinVel,
		double lifeTime,
		bool autofade);

	float getRemainingLifetime() const;

	// Inherited via Billboard : Entity
	virtual void Step(float deltaTime) override;
};
