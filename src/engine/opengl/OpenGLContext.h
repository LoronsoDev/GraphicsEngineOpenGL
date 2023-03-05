#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>
#include <engine/base/GraphicsContext.h>
#include <engine/render/PolygonUtils.h>
#include <scene/Object.h>
#include <map>
namespace engine
{
	class OpenGL1Context : public GraphicsContext
	{
	public:
		OpenGL1Context() { }

		// Inherited via GraphicsContext
		virtual void Init(Window* window) override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_ContextWindow;

		// Inherited via GraphicsContext
		virtual void SetupObject(Object* obj) override;
		virtual void RemoveObject(Object* obj) override;
		virtual void DrawObjects(std::vector<Object*>* objs) override;

		// Inherited via GraphicsContext
		virtual bool IsClosed() override;
		virtual int GetWidth() override;
		virtual int GetHeight() override;
	};


	class OpenGL4Context : public GraphicsContext
	{
	public:
		typedef struct VBO_t {
			GLuint boId;
			GLuint vbo;
			GLuint idxbo;
		}VBO_t;

		std::map<int, VBO_t> bufferObjectList;
		OpenGL4Context() { }

		// Inherited via GraphicsContext
		virtual void Init(Window* window) override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_ContextWindow;

		// Inherited via GraphicsContext
		virtual void SetupObject(Object* obj) override;//modificar
		virtual void RemoveObject(Object* obj) override;//modificar
		virtual void DrawObjects(std::vector<Object*>* objs) override;//modificar

		// Inherited via GraphicsContext
		virtual bool IsClosed() override;
		virtual int GetWidth() override;
		virtual int GetHeight() override;
	};

}