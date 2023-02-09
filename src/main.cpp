#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>
#include <engine/base/Window.h>

using namespace engine;

int main(int chargc, char** argv)
{
	Window* window = Window::Create();
	
	//Main update loop.
	while (true)
	{
		window->OnUpdate();
	}

}