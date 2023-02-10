#pragma once

#include <engine/opengl/OpenGLContext.h>

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

		static GraphicsContext* CreateRenderer();
		static inline RendererBackend GetRendererBackend() { return s_RenderingBackend; }
	};

}