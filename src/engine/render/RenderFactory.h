#pragma once

#include <engine/base/Window.h>
#include <engine/base/GraphicsContext.h>
#include <engine/base/InputManager.h>

namespace engine
{
	static class RenderFactory
	{
		enum RendererBackend
		{
			OPENGL1,
			OPENGL4,
			VULKAN,
			DIRECT3D,
			UNDEFINED
		};

		static RendererBackend s_RenderingBackend;

	public:
		RenderFactory() = default;

		static inline RendererBackend GetRendererBackend() { return s_RenderingBackend; }
		static GraphicsContext* CreateRenderer(Window* window);
	};

}