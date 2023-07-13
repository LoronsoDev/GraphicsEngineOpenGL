#pragma once

#include <scene/Object3D.h>

class Billboard : public Object3D
{
private:
	float spin = 1.0f;

public:

	Billboard() = default;
	float getSpin() const { return spin; }
	void setSpin(float spin) { this->spin = spin; }
	virtual void ComputeModelMatrix() override;

	// Inherited via Entity
	virtual void Step(float deltaTime) override;
};

