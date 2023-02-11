#pragma once

#define GLAD_ONLY_HEADERS
#include <Engine_Core.h>
#include <engine/base/InputManager.h>


namespace engine
{
class GraphicsContext;

	//Generic class for any implementation of Window.
	class Window
	{
	public:
		struct WindowProps
		{
			unsigned int Width, Height;
			std::string Title;

			bool VSync = true;
			bool isRunning = true;

			InputManager* InputManager = nullptr;
			GraphicsContext* GraphicsContext = nullptr;

			WindowProps(const std::string& title = "3D ENGINE BASE WINDOW",
				unsigned int w = 1280,
				unsigned int h = 720)
				:Title(title), Width(w), Height(h) {}
		};

		WindowProps m_WindowProperties;

	public:
		virtual ~Window() {};

		virtual void OnUpdate() = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSyncEnabled() = 0;

		inline virtual unsigned int GetWidth() const { return m_WindowProperties.Width; }
		inline virtual unsigned int GetHeight() const { return m_WindowProperties.Height; }

		/// <returns> Native implementation of Window (e.g. GLFWwindow* in the case of GLFW) </returns>
		inline virtual void* GetNativeWindow() const = 0;
		virtual void Shutdown() = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}
