#pragma once

#define GLAD_ONLY_HEADERS

#include "InputManager.h"
#include "scene/Render.h"
#include <engine/render/RenderFactory.h>

class Kernel
{
	static Render* m_Render;
	static engine::InputManager* m_InputManager;
	static std::vector<Object*>* m_Objects;
	static bool m_End;

public:
	static void InitKernel();
	static void AddObject(Object* obj) { m_Objects->push_back(obj); };
	static void Exit();
	static void Execute();
};
