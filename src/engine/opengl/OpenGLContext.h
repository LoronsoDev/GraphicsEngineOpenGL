#define GLAD_ONLY_HEADERS

#include <engine/base/GraphicsContext.h>
#include <Engine_Core.h>

namespace engine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window) : m_ContextWindow(window) {}

		// Inherited via GraphicsContext
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_ContextWindow;
	};
}