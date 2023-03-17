#include <engine/base/UserInterface.h>
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
	auto props = *static_cast<WindowProps*>(glfwGetWindowUserPointer(m_Window));
	props.isRunning = false;

	glfwTerminate();
	glfwDestroyWindow(m_Window);
}

void WindowsWindow::Init(const WindowProps& props)
{
	if (!s_GLFWInitialized)
	{
		const int success = glfwInit();

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

	m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), props.Title.c_str(), nullptr, nullptr);
	SetVSync(props.VSync);
	SetupInputCallbacks();
	std::cout << "\n GLFW WINDOW CREATED SUCCESFULLY \n";

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPos(m_Window, 0.0, 0.0);
	m_InputManager->isMouseHidden = true;

	glfwSetWindowUserPointer(m_Window, &m_WindowProperties); //Adds a user pointer that is returned for every callback.

	//Context is created by the Kernel now.
	m_Context = RenderFactory::CreateRenderer();

	m_Context->Init(this);

	m_WindowProperties.GraphicsContext = m_Context;

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

			props.InputManager->lastMousePosX = props.InputManager->mousePosX;
			props.InputManager->lastMousePosY = props.InputManager->mousePosY;

			props.InputManager->mousePosX = x;
			props.InputManager->mousePosY = y;
		}
	);

	glfwSetScrollCallback(m_Window,
		[](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto props = *(WindowProps*)glfwGetWindowUserPointer(window);

			props.InputManager->scrollOffsetX = (float)xOffset;
			props.InputManager->scrollOffsetY = (float)yOffset;
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

	if(ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard)
	{
		m_InputManager->isUIInput = true;
	}
	else
	{
		m_InputManager->isUIInput = false;

		if (m_InputManager->GetKeyState(GLFW_MOUSE_BUTTON_1))
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

	}

	if(m_InputManager->GetKeyState(GLFW_KEY_ESCAPE) == 1)
	{
		m_WindowProperties.isRunning = false;
	}


	if(glfwWindowShouldClose(m_Window))
		m_WindowProperties.isRunning = false;
}

void WindowsWindow::SetVSync(bool enabled)
{
	glfwSwapInterval((int)enabled);

	m_WindowProperties.VSync = enabled;
}

bool WindowsWindow::IsVSyncEnabled()
{
	return m_WindowProperties.VSync;
}