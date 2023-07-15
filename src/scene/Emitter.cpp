#include "Emitter.h"
#include <engine/base/Kernel.h>

Emitter::Emitter(const char* mshFile, float emissionRate, bool autoFade)
{
	this->mshFile = mshFile;
	this->emissionRate = emissionRate;
	this->autoFade = autoFade;
}

void Emitter::Step(float deltaTime)
{
	//calcular nuevas partículas
	double newParticleCount = particleAccum + ((double)emissionRate) * deltaTime;
	int particlesToCreate = (int)newParticleCount;
	particleAccum = newParticleCount - (double)particlesToCreate;

	for (int i = 0; i < particlesToCreate; i++)
	{
		auto vel = glm::linearRand(velRange[0], velRange[1]);
		double spinVel = glm::linearRand(spinVelRange[0], spinVelRange[1]);
		double lifeTime = glm::linearRand(lifetimeRange[0], lifetimeRange[1]);
		Particle * p = new Particle(
			mshFile,
			vel,
			spinVel,
			lifeTime,
			autoFade);
		p->name = "Particle";
		p->SetPos(this->GetPos());
		p->SetRot({ 0., 3.14, 0., 0. });
		double scale = glm::linearRand(scaleRange[0], scaleRange[1]);
		p->SetScale(glm::vec4(glm::vec3(scale), 1.0f));
		p->ComputeModelMatrix();

		p->isDynamicObject = true;
		particleList.push_back(p);
	}
	Camera* c = (*Kernel::s_Cameras)[0];
	std::map<float, Particle*> distMap;

	for (auto p : particleList)
	{
		if (p->getRemainingLifetime() > 0) {
			p->Step(deltaTime);
			float dist = glm::distance(glm::vec3(p->GetPos()), c->GetPos());
			distMap[dist] = p;
		}
		else
		{
			delete p;
		}
	}
	particleList.clear();

	for (auto p : distMap)
	{
		particleList.push_back(p.second);
	}
}

void Emitter::setRateRange(float min, float max)
{
	rateRange[0] = min;
	rateRange[1] = max;
}

void Emitter::setVelocityRange(const glm::vec3& min, const glm::vec3& max)
{
	velRange[0] = min;
	velRange[1] = max;
}

void Emitter::setSpinVelocityRange(float min, float max)
{
	spinVelRange[0] = min;
	spinVelRange[1] = max;
}

void Emitter::setScaleRange(float min, float max)
{
	scaleRange[0] = min;
	scaleRange[1] = max;
}

void Emitter::setLifetimeRange(float min, float max)
{
	lifetimeRange[0] = min;
	lifetimeRange[1] = max;
}

void Emitter::setColorRange(const glm::vec4& min, const glm::vec4& max)
{
	colorRange[0] = min;
	colorRange[1] = max;
}

void Emitter::emit(bool enable)
{
	emitting = enable;
}

bool Emitter::isEmitting()
{
	return emitting;
}

std::list<Particle*>* Emitter::getParticleList()
{
	return &particleList;
}
