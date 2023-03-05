#pragma once

#define GLAD_ONLY_HEADERS

#include "InputManager.h"
#include <engine/base/GraphicsContext.h>
#include <engine/render/RenderFactory.h>
#include <engine/base/Window.h>

using namespace engine;

class Kernel
{
public:

	static Window* s_Window;
	static GraphicsContext* s_GraphicsContext;
	static engine::InputManager* s_InputManager;
	static std::vector<Object*>* s_Objects;
	static bool s_End;

	Kernel();
	static void Init();
	static void AddObject(Object* obj);
	static void Exit();
	static void Execute();
};
