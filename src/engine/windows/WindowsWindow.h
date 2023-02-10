#pragma once

#include <engine/base/Window.h>
#include <engine/opengl/OpenGLContext.h>
#include <engine/windows/GLFWInputManager.h>

namespace engine
{
	class WindowsWindow : public Window
	{
	public:
		static bool s_GLFWInitialized;

		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		// Inherited via Window
		virtual void OnUpdate() override;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSyncEnabled() override;

		inline virtual void* GetNativeWindow() const override { return m_Window; }
	private:
		void Init(const WindowProps& props);
		void Shutdown();

		void SetupInputCallbacks();

	private:
		GLFWInputManager* m_InputManager;
		GraphicsContext* m_Context;
		GLFWwindow* m_Window;
	};

}