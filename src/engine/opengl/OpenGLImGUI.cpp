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
		userPath = fileBrowser.GetSelected().string();
		std::cout << "Selected filename at path : \n     " << fileBrowser.GetSelected().string() << std::endl;
	}

	int windowIndex = 0;
	for(ModifiableIngameItem* item : sceneObjects)
	{
		std::string title = "[" + std::to_string(++windowIndex) + "] " + item->item_type_id;

		ImGui::SetNextWindowBgAlpha(0.3f);
		ImGui::Begin(title.c_str());
		{
			ImGui::Text("Position:");
			ImGui::SliderFloat("X pos", &item->userPos.x, -10, 10);
			ImGui::SliderFloat("Y pos", &item->userPos.y, -10, 10);
			ImGui::SliderFloat("Z pos", &item->userPos.z, -10, 10);

			ImGui::Text("Rotation:");
			ImGui::SliderAngle("X rot", &item->userRot.x);
			ImGui::SliderAngle("Y rot", &item->userRot.y);
			ImGui::SliderAngle("Z rot", &item->userRot.z);
			ImGui::SliderAngle("W rot", &item->userRot.w);

			ImGui::Text("Scale:");

			ImGui::Checkbox("Scale per axis", &item->scalePerAxis);
			if (item->scalePerAxis)
			{
				ImGui::SliderFloat("X scale", &item->userScale.x, -50, 50);
				ImGui::SliderFloat("Y scale", &item->userScale.y, -50, 50);
				ImGui::SliderFloat("Z scale", &item->userScale.z, -50, 50);
				ImGui::SliderFloat("W scale", &item->userScale.w, -50, 50);
			}
			else
			{
				ImGui::DragFloat("Scale", &item->uniformScale);
				item->userScale = { item->uniformScale, item->uniformScale, item->uniformScale, 1.0f };
			}

		}
		ImGui::End();

	}
	
	for (ModifiableIngameItem* item : sceneLights)
	{
		std::string title = "[" + std::to_string(++windowIndex) + "] " + item->item_type_id;

		ImGui::SetNextWindowBgAlpha(0.3f);
		ImGui::Begin(title.c_str());
		{
			ImGui::Text("Position:");
			ImGui::SliderFloat("X pos", &item->userPos.x, -10, 10);
			ImGui::SliderFloat("Y pos", &item->userPos.y, -10, 10);
			ImGui::SliderFloat("Z pos", &item->userPos.z, -10, 10);

			ImGui::Text("Direction:");
			ImGui::SliderAngle("X rot", &item->userRot.x);
			ImGui::SliderAngle("Y rot", &item->userRot.y);
			ImGui::SliderAngle("Z rot", &item->userRot.z);
			
			ImGui::Text("Attenuation:");
			ImGui::DragFloat("Intensity", &item->userScale.z, 0.01, 0.01, 10);
			ImGui::DragFloat("Linear attenuation", &item->userScale.x, 0.01, 0, 5);
			ImGui::DragFloat("Quadratic attenuation", &item->userScale.y, 0.01, 0, 5);

			ImGui::Text("Parameters");
			ImGui::ColorPicker4("Color", &item->auxValues[0]);
		}
		ImGui::End();
	}


	
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
