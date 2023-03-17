#include "OpenGLImGUI.h"

#include <thirdparty/imfilebrowser.h>

void OpenGLImGUI::CreateContext(engine::Window * window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	io.ConfigDockingWithShift = true;

	this->window = window;
	this->renderingWindow = (GLFWwindow*)window->GetNativeWindow();
}

ImGui::FileBrowser fileBrowser;
void OpenGLImGUI::Init()
{
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)renderingWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	fileBrowser = ImGui::FileBrowser(ImGuiFileBrowserFlags_NoModal);
	fileBrowser.SetTypeFilters({ ".msh" });

	if (ImGui::GetCurrentContext())
		std::cout << " IMGUI FOR GLFW INITIALIZED SUCCESFULLY\n";
	else
		std::cout << "\n ERROR CREATING IMGUI CONTEXT FOR GLFW/OPENGL\n ";
}

void OpenGLImGUI::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::GetIO().DisplaySize = ImVec2(window->m_WindowProperties.Width, (window->m_WindowProperties.Height));


	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("InvisibleWindow", nullptr, windowFlags);
	ImGui::PopStyleVar(3);


	ImGuiID dockSpaceID = ImGui::GetID("InvisibleWindowDockSpace");
	ImGui::DockSpace(dockSpaceID, { 0,0 }, ImGuiDockNodeFlags_PassthruCentralNode);
	ImGui::End();

	ImGui::SetNextWindowBgAlpha(0.3f);
	ImGui::Begin("Load object");
	{
		if (ImGui::Button("Load new .MSH file"))
		{
			fileBrowser.Open();
		}
	}
	ImGui::End();

	fileBrowser.Display();

	if (fileBrowser.HasSelected())
	{
		//Load .MSH on here...
		std::cout << "Selected filename at path : \n     " << fileBrowser.GetSelected().string() << std::endl;
	}

	ImGui::SetNextWindowBgAlpha(0.3f);
	ImGui::Begin("Object settings");
	{
		ImGui::Text("Position:");
		ImGui::SliderFloat("X pos", &userPos.x, -10, 10);
		ImGui::SliderFloat("Y pos", &userPos.y, -10, 10);
		ImGui::SliderFloat("Z pos", &userPos.z, -10, 10);

		ImGui::Text("Rotation:");
		ImGui::SliderAngle("X rot", &userRot.x);
		ImGui::SliderAngle("Y rot", &userRot.y);
		ImGui::SliderAngle("Z rot", &userRot.z);
		ImGui::SliderAngle("W rot", &userRot.w);

	}
	ImGui::End();
}

void OpenGLImGUI::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void OpenGLImGUI::Shutdown()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
