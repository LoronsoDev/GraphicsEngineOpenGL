#include "Billboard.h"
#include <engine/base/Kernel.h>

void Billboard::ComputeModelMatrix()
{
	Camera * cam = (*Kernel::s_Cameras)[0];

	auto pMat = cam->getProjection();
	auto vMat = cam->getView();
	auto VP = pMat * vMat;

	VP[0][3] = this->GetPos().x;
	VP[1][3] = this->GetPos().y;
	VP[2][3] = this->GetPos().z;
	VP[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	VP = glm::transpose(VP);
	VP = glm::rotate(VP, this->GetRot().x, glm::vec3(1.0f, 0.0f, 0.0f));
	VP = glm::rotate(VP, this->GetRot().y, glm::vec3(0.0f, 1.0f, 0.0f));
	VP = glm::rotate(VP, this->GetRot().z, glm::vec3(0.0f, 0.0f, 1.0f));
	VP = glm::scale(VP, glm::vec3(this->GetScale()));

	this->SetModelMatrix(VP);
}

void Billboard::Step(float deltaTime)
{

}
