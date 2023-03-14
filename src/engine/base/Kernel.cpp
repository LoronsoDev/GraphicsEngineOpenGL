#include "Kernel.h"

#include <functional>

#include "engine/windows/WindowsWindow.h"

Window* Kernel::s_Window = nullptr;
GraphicsContext* Kernel::s_GraphicsContext = nullptr;
InputManager* Kernel::s_InputManager = nullptr;
std::vector<Object*>* Kernel::s_Objects = nullptr;
std::vector<Camera*>* Kernel::s_Cameras = nullptr;

bool Kernel::s_End = false;


Kernel::Kernel() = default;

void Kernel::Init()
{
	s_Window = engine::Window::Create();
	s_GraphicsContext = s_Window->m_WindowProperties.GraphicsContext;
	s_InputManager = s_Window->m_WindowProperties.InputManager;

	s_Objects = new std::vector<Object*>();
	s_Cameras = new std::vector<Camera*>();
}

void Kernel::AddObject(Object* obj)
{
	s_Objects->push_back(obj);
	s_GraphicsContext->SetupObject(obj);
}

void Kernel::AddCamera(Camera* cam)
{
	s_Cameras->push_back(cam);
	//Sets up camera, sets as main camera if it's the first one added.
	s_GraphicsContext->SetupCamera(cam, s_Cameras->size() == 1);

	cam->computeProjectionMatrix((s_Window->GetWidth() + 0.0f) / s_Window->GetHeight());
}


void Kernel::Exit()
{
	s_Window->Shutdown();
	
	delete s_GraphicsContext;
	delete s_InputManager;
	delete s_Objects;
}

void Kernel::Execute()
{
	float newTime = 0;
	float deltaTime = 0;
	float lastTime = 0;

	//Main update loop.
	while (!s_End)
	{
		newTime = static_cast<float>(glfwGetTime());
		deltaTime = newTime - lastTime;
		lastTime = newTime;

		s_Window->OnUpdate();

		for(Camera* cam : *s_Cameras)
		{
			cam->Step(deltaTime);
			cam->computeViewMatrix();
		}

		for(Object* obj : *s_Objects)
		{
			obj->Step(deltaTime);
			obj->ComputeModelMatrix();
		}

		s_GraphicsContext->DrawObjects(s_Objects);

		//END
		if(!s_Window->m_WindowProperties.isRunning)
		s_End = true;
	}
}
