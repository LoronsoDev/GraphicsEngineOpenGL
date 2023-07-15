#include "Kernel.h"

#include <functional>

#include "engine/windows/WindowsWindow.h"

Window* Kernel::s_Window = nullptr;
GraphicsContext* Kernel::s_GraphicsContext = nullptr;
InputManager* Kernel::s_InputManager = nullptr;
std::vector<Object*>* Kernel::s_Objects = nullptr;
std::vector<Camera*>* Kernel::s_Cameras = nullptr;
std::vector<Light*>* Kernel::s_Lights = nullptr;
std::vector<Emitter*>* Kernel::s_Emitters = nullptr;

bool Kernel::s_End = false;


Kernel::Kernel() = default;

void Kernel::Init()
{
	s_Window = engine::Window::Create();
	s_GraphicsContext = s_Window->m_WindowProperties.GraphicsContext;
	s_InputManager = s_Window->m_WindowProperties.InputManager;

	s_Objects = new std::vector<Object*>();
	s_Cameras = new std::vector<Camera*>();
	s_Lights = new std::vector<Light*>();
	s_Emitters = new std::vector<Emitter*>();
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

void Kernel::AddLight(Light* light)
{
	s_Lights->push_back(light);
}

void Kernel::AddEmitter(Emitter* emitter)
{
	s_Emitters->push_back(emitter);
}


void Kernel::Exit()
{
	s_Window->Shutdown();
	
	delete s_GraphicsContext;
	delete s_InputManager;
	delete s_Objects;
	delete s_Lights;
	delete s_Cameras;
	delete s_Emitters;
}

void Kernel::Execute()
{
	float newTime = 0;
	float deltaTime = 0;
	float lastTime = 0;

	s_GraphicsContext->SetupLighting(s_Lights, &ambientLight);
	
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

		for(Light * l : *s_Lights)
		{
			l->step(deltaTime);
		}
		s_GraphicsContext->ClearFlags();

		for(Emitter * e : *s_Emitters)
		{
			e->Step(deltaTime);
			const auto pList = e->getParticleList();
			std::vector<Object*> pList_to_vector(pList->begin(), pList->end());
			for(Object * p : pList_to_vector)
			{
				s_GraphicsContext->SetupObject(p);
			}
			s_GraphicsContext->DrawObjects(&pList_to_vector);
		}

		s_GraphicsContext->DrawObjects(s_Objects);

		s_GraphicsContext->PostRender();
		s_GraphicsContext->SwapBuffers();

		//END
		if(!s_Window->m_WindowProperties.isRunning)
			s_End = true;
	}
}
