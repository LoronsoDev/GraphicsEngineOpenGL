#include "GLFWInputManager.h"

engine::GLFWInputManager::GLFWInputManager()
{
	Init();
}

void engine::GLFWInputManager::Init()
{
	for (int i = 0; i < GLFW_KEY_LAST; ++i)
	{
		keybEvent[i] = (int)KeyState::RELEASE;
	}

	mousePosX = mousePosY = lastMousePosX = lastMousePosY = 0;
}

int engine::GLFWInputManager::GetKeyState(int key)
{
	return keybEvent[key];
}