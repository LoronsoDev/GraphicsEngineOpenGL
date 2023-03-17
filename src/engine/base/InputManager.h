#pragma once

#include <Engine_Core.h>

namespace engine
{
	class InputManager
	{
	public:
		//map key is pressed key identifier.
		std::unordered_map<int, int> keybEvent;

		// mouse
		int mousePosX, mousePosY;
		int lastMousePosX, lastMousePosY;

		float scrollOffsetX, scrollOffsetY;

		bool isUIInput = false;
		bool isMouseHidden = false;

		virtual void Init() = 0;
		virtual int GetKeyState(int key) = 0;

		virtual ~InputManager(){}
	};
}