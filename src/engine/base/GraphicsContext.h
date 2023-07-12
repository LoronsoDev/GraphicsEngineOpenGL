#pragma once

#include <engine/base/Window.h>
#include <scene/Object.h>
#include <scene/Camera.h>
#include <scene/Light.h>

namespace engine
{
	class GraphicsContext
	{
	public:
		virtual void Init(Window* renderWindow) = 0;
		virtual void SwapBuffers() = 0;

		virtual void SetupCamera(Camera* cam, bool isMainCam = true) = 0;
		virtual void SetupLighting(std::vector<Light*>* lights, glm::vec3 * ambient) = 0;	//Pointers owned by the caller
		virtual void SetupObject(Object* obj) = 0;
		virtual void RemoveObject(Object* obj) = 0;
		virtual void DrawObjects(std::vector<Object*>* objs) = 0;

		inline virtual bool IsClosed() = 0;
		inline virtual int GetWidth() = 0;
		inline virtual int GetHeight() = 0;

		virtual ~GraphicsContext() {};

	protected:
		//Main camera rendering the scene.
		Camera* m_MainCamera = nullptr;
		Window* m_RenderWindow = nullptr;
	};
}