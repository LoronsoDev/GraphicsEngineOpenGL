#define GLAD_ONLY_HEADERS

#include <engine/base/Kernel.h>

#include "scene/Object3D.h"

class TrianguloRot : Object3D
{
public:
	TrianguloRot()
	{
		Mesh3D *mesh = new Mesh3D;

		Vertex vertices[3];

		mesh->AddVertex({ {-0.5f,-0.5f,0.f,1.f} });
		mesh->AddVertex({ {0.5f, -0.5f, 0.0f, 1.0f} });
		mesh->AddVertex({ {0.f, 0.5f, 0.0f, 1.0f} });

		SetMesh(mesh);
	}

	void Step(double dt) override
	{
		//esto por que iria aqui? idk
		if (Kernel::s_InputManager->GetKeyState(GLFW_KEY_E) > 0)
		{
			Kernel::s_End = true;
		}

		glm::vec4 newRot = GetRot() + glm::vec4{0.f,  (3.14159f * 0.25f) * dt,0.f,0.f};
		
		SetRot(newRot);
	}
};

int main(int chargc, char** argv)
{
	SELECT_RENDERER(OPENGL1);

	Kernel::Init();

	TrianguloRot triangle;
	Kernel::AddObject(reinterpret_cast<Object3D*>(&triangle));

	Kernel::Execute();
	Kernel::Exit();
}