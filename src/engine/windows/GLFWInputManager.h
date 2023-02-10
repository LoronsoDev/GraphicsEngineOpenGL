#pragma once
#define GLAD_ONLY_HEADERS

#include <engine/base/InputManager.h>

namespace engine
{
	class GLFWInputManager : public InputManager
	{
	public:
		enum KeyState
		{
			RELEASE = 0, //Unpressed
			PRESS,	//Pressed
			REPEAT	//Pressed, repeating key
		};

		GLFWInputManager();

		// Inherited via InputManager
		virtual void Init() override;
		virtual int GetKeyState(int key) override;
	};
}
