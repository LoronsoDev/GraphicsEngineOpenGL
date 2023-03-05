#include <engine/render/RenderFactory.h>

namespace engine
{
	engine::RenderFactory::RendererBackend engine::RenderFactory::s_RenderingBackend = RenderFactory::RendererBackend::OPENGL1;

	GraphicsContext* RenderFactory::CreateRenderer()
	{
		switch (s_RenderingBackend)
		{
		case RendererBackend::OPENGL1:
			return new OpenGL1Context();
		case RendererBackend::OPENGL4:
			return new OpenGL4Context();
		}

		std::cout << "ERROR: Selected renderer isn't supported yet. Can't create graphics context. \n";
		assert(false);

		return nullptr;
	}
}