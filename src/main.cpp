#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>
#include <engine/base/Window.h>

int main(int chargc, char** argv)
{
	engine::Window* window = engine::Window::Create();

	//Main update loop.
	while (true)
	{
		window->OnUpdate();
	}
}