#pragma once

#include <engine/opengl/OpenGLContext.h>

#define SELECT_RENDERER(BACKEND) engine::RenderFactory::s_RenderingBackend = engine::RenderFactory::##BACKEND

namespace engine
{
	static class RenderFactory
	{
	public:
		enum RendererBackend
		{
			OPENGL1,
			OPENGL4,
			VULKAN,
			DIRECT3D,
			UNDEFINED
		};

		static RendererBackend s_RenderingBackend;

		RenderFactory() = default;

		static GraphicsContext* CreateRenderer();
		static inline RendererBackend GetRendererBackend() { return s_RenderingBackend; }
	};
}