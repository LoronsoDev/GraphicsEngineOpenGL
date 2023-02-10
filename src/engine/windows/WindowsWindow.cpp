#include <engine/windows/WindowsWindow.h>

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
	auto props = *(WindowProps*)glfwGetWindowUserPointer(m_Window);
	props.isRunning = false;

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

	glfwSetWindowUserPointer(m_Window, &m_WindowProperties); //Adds a user pointer that is returned for every callback.

	//OpenGL Context
	m_Context = RenderFactory::CreateRenderer((Window*) m_Window);
	m_Context->Init();

	assert(m_Window); // Window or OpenGL context creation failed
}

//Setup all GLFW input callbacks here.
void engine::WindowsWindow::SetupInputCallbacks()
{
	m_InputManager = new GLFWInputManager();
	m_InputManager->Init();

	m_WindowProperties.InputManager = m_InputManager;
	
	glfwSetKeyCallback(m_Window,
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto props = *(WindowProps*)glfwGetWindowUserPointer(window);
			props.InputManager->keybEvent[key] = action;
		}
		);

	glfwSetMouseButtonCallback(m_Window,
		[](GLFWwindow* window, int button, int action, int mods)
		{
			auto props = *(WindowProps*)glfwGetWindowUserPointer(window);
			props.InputManager->keybEvent[button] = action;
		}
	);

	glfwSetCursorPosCallback(m_Window,
		[](GLFWwindow* window, double x, double y)
		{
			auto props = *(WindowProps*)glfwGetWindowUserPointer(window);

			props.InputManager->lastMousePosX = (int)props.InputManager->mousePosX;
			props.InputManager->lastMousePosY = (int)props.InputManager->mousePosY;

			props.InputManager->mousePosX = (int)x;
			props.InputManager->mousePosY = (int)y;
		}
	);

	glfwSetScrollCallback(m_Window,
		[](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto props = *(WindowProps*)glfwGetWindowUserPointer(window);

			props.InputManager->scrollOffsetX = (float) xOffset;
			props.InputManager->scrollOffsetY = (float) yOffset;
		}
	);

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			auto props = *(WindowProps*)glfwGetWindowUserPointer(window);

			props.Width = width;
			props.Height = height;
		});
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
