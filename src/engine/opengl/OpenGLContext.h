#define GLAD_ONLY_HEADERS

#include <engine/base/GraphicsContext.h>
#include <Engine_Core.h>

namespace engine
{
	class OpenGL1Context : public GraphicsContext
	{
	public:
		OpenGL1Context(GLFWwindow* window) : m_ContextWindow(window) {}

		// Inherited via GraphicsContext
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_ContextWindow;

		// Inherited via GraphicsContext
		virtual void SetupObject(Object* obj) override;
		virtual void RemoveObject(Object* obj) override;
		virtual void DrawObjects(std::vector<Object*>* objs) override;
	};
}