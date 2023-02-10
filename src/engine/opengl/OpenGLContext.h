#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>
#include <engine/base/GraphicsContext.h>
#include <engine/render/PolygonUtils.h>
#include <scene/Object.h>

namespace engine
{
	class OpenGL1Context : public GraphicsContext
	{
	public:
		OpenGL1Context() { }

		// Inherited via GraphicsContext
		virtual void Init(Window* window) override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_ContextWindow;

		// Inherited via GraphicsContext
		virtual void SetupObject(Object* obj) override;
		virtual void RemoveObject(Object* obj) override;
		virtual void DrawObjects(std::vector<Object*>* objs) override;

		// Inherited via GraphicsContext
		virtual bool IsClosed() override;
		virtual int GetWidth() override;
		virtual int GetHeight() override;

		~OpenGL1Context() {}
	};
}