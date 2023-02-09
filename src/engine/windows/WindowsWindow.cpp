#include "WindowsWindow.h"

using namespace engine;

bool WindowsWindow::s_GLFWInitialized = false;

Window* Window::Create(const WindowProps& props)
{
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
    Init(props);
}

WindowsWindow::~WindowsWindow()
{
	Shutdown();
}

void WindowsWindow::Shutdown()
{
	glfwTerminate();
    glfwDestroyWindow(m_Window);
}

void WindowsWindow::Init(const WindowProps& props)
{

	if (!s_GLFWInitialized)
	{
		int success = glfwInit();

		assert(success);
		//Only reaches here if it's initialized.

		s_GLFWInitialized = success;
	}

#ifdef __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#endif

	m_Window = glfwCreateWindow((int) props.Width, (int) props.Height, props.Title.c_str(), nullptr, nullptr);
	SetVSync(props.VSync);
	SetupInputCallbacks();
	std::cout << "\n GLFW WINDOW CREATED SUCCESFULLY \n";


	//OpenGL Context
	m_Context = new OpenGLContext(m_Window);
	m_Context->Init();

	assert(m_Window); // Window or OpenGL context creation failed
}

void engine::WindowsWindow::SetupInputCallbacks()
{
	//Setup all input callbacks here.
}

void WindowsWindow::OnUpdate()
{
	glfwPollEvents();
	m_Context->SwapBuffers();
}

void WindowsWindow::SetVSync(bool enabled)
{
	glfwSwapInterval((int) enabled);

	m_WindowProperties.VSync = enabled;
}

bool WindowsWindow::IsVSyncEnabled()
{
	return m_WindowProperties.VSync;
}
