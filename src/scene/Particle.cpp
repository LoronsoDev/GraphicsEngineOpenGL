#include "Particle.h"

Particle::Particle(std::string mshFile, const glm::vec3& vel, float spinVel, double lifeTime, bool autoFade)
{
	this->vel = vel;
	this->lifeTime = lifeTime;
	this->setSpin(spinVel);
	this->autoFade = autoFade;
	this->LoadDataFromFile(mshFile);
}

float Particle::getRemainingLifetime() const
{
	return glm::clamp(lifeTime - timeLivedTimer, 0.0, lifeTime);
}

void Particle::Step(float deltaTime)
{
	timeLivedTimer += deltaTime;

	auto lastPos = this->GetPos();
	auto newPos = lastPos + (vel * deltaTime);
	this->SetPos(newPos);
	auto rot = this->GetRot();
	rot.z += ( (this->getSpin() * 3.14f) / 180.f) * deltaTime;
	this->SetRot(rot);
	if (autoFade)
	{
		auto fade = 1 - glm::clamp(timeLivedTimer/lifeTime, 0.0, 1.0);
		this->GetMeshes()[0]->getMaterial()->alpha = fade;
	}

	this->ComputeModelMatrix();
};