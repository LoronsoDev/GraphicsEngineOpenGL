#pragma once

#include <scene/Object3D.h>
#include <scene/Camera.h>

class Billboard : public Object3D
{
private:
	float spin = 1.0f;

public:
	Billboard() = default;
	float getSpin() const { return spin; }
	void setSpin(float spin) { this->spin = spin; }

	// Inherited via Entity
	virtual void Step(float deltaTime) override;
	virtual void ComputeModelMatrix() override;
};
