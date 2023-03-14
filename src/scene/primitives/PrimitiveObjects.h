#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>
#include <scene/Object3D.h>
#include <engine/opengl/GLSLMaterial.h>
#include <engine/render/RenderFactory.h>
#include <engine/base/Kernel.h>

class CubeTex : public Object3D
{
	Material* mat;

public:
	CubeTex();
	void Step(float deltaTime) override;
};

class Triangle : public Object3D
{
	Material* mat;

public:
	Triangle()
	{
		Mesh3D* mesh = new Mesh3D;

		//Adding here materials as the provided structure says so.

		mesh->setMaterial(new GLSLMaterial);
		mat = mesh->getMaterial();

		mat->loadPrograms("Shaders/color_unlit.vert", "Shaders/color_unlit.frag");


		mesh->AddVertex({ {-0.5f,-0.5f,0.f,1.f} });
		mesh->AddVertex({ {0.5f, -0.5f, 0.0f, 1.0f} });
		mesh->AddVertex({ {0.f, 0.5f, 0.0f, 1.0f} });

		mesh->addTriangle(0, 1, 2);

		AddMesh(mesh);
	}

	void Step(float dt) override
	{
		//esto por que iria aqui? idk esta aqui porque lo pone en la practica.
		if (Kernel::s_InputManager->GetKeyState(GLFW_KEY_E) > 0)
		{
			Kernel::s_End = true;
		}

		glm::vec4 newRot = GetRot() + glm::vec4{ 0.f,  (3.14159f * 0.25f) * dt,0.f,0.f };

		//program->setVec4("position", { .4f, .5f, .1f, .2f });

		SetRot(newRot);
	}
};