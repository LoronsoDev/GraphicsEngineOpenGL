#pragma once

#include <engine/base/Window.h>
#include <scene/Object.h>


namespace engine
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		virtual void SetupObject(Object* obj) = 0;
		virtual void RemoveObject(Object* obj) = 0;
		virtual void DrawObjects(std::vector<Object*>* objs) = 0;

		inline virtual bool IsClosed() { return m_RenderWindow->m_WindowProperties.isRunning; };
		inline virtual int GetWidth()	{ return m_RenderWindow->m_WindowProperties.Width; };
		inline virtual int GetHeight()  { return m_RenderWindow->m_WindowProperties.Width; };

	private:
		Window* m_RenderWindow;
	};
}