#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <engine/base/UserInterface.h>
#include <GLFW/glfw3.h>

class OpenGLImGUI : public UserInterface
{
	//parameters changed by the UI.
public:

	struct ModifiableIngameItem
	{
		std::string item_type_id = "OBJECT";
		glm::vec3 userPos = glm::vec3(0);
		glm::vec4 userRot = glm::vec4(0);
		glm::vec4 userScale = glm::vec4(1);
		float uniformScale = 1.0f;

		bool scalePerAxis = false;

		glm::vec4 auxValues = glm::vec4(-1.f); //Used for aux stuff
	};

	std::vector<ModifiableIngameItem*> sceneObjects;
	std::vector<ModifiableIngameItem*> sceneLights;

	std::string userPath = "";

private:
	engine::Window * window = nullptr;
	GLFWwindow* renderingWindow = nullptr;

public:
	void CreateContext(engine::Window* window) override;
	void Init() override;
	void Update() override;
	void Render() override;
	void Shutdown() override;
};

