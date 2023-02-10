#pragma once

#include <engine/base/Window.h>
#include <scene/Object.h>

namespace engine
{
	class GraphicsContext
	{
	public:
		virtual void Init(Window* renderWindow) = 0;
		virtual void SwapBuffers() = 0;

		virtual void SetupObject(Object* obj) = 0;
		virtual void RemoveObject(Object* obj) = 0;
		virtual void DrawObjects(std::vector<Object*>* objs) = 0;

		inline virtual bool IsClosed() = 0;
		inline virtual int GetWidth() = 0;
		inline virtual int GetHeight() = 0;
	private:
		Window* m_RenderWindow = nullptr;
	};
}