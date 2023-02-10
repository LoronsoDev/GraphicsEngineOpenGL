#include <engine/render/RenderFactory.h>

namespace engine
{
	#define SELECT_RENDERER(BACKEND) RenderFactory::RendererBackend RenderFactory::s_RenderingBackend = RenderFactory::RendererBackend::##BACKEND


	/* BACKENDS...

		OPENGL1,
		OPENGL4,
		VULKAN,
		DIRECT3D,
		UNDEFINED

	*/

	SELECT_RENDERER(OPENGL1);

	GraphicsContext* RenderFactory::CreateRenderer(Window* window)
	{
		return nullptr;
	}

}