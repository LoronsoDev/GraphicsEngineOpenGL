#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>
#include <engine/base/GraphicsContext.h>
#include <engine/opengl/GLSLMaterial.h>
#include <scene/Camera.h>

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
		GLFWwindow* m_ContextWindow = nullptr;

		// Inherited via GraphicsContext
		virtual void SetupCamera(Camera* cam, bool isMainCam = true) override {} //No cameras in GL1
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

		VBO_t vbo;

		std::map<int, VBO_t> bufferObjectList;
		OpenGL4Context() { }

		// Inherited via GraphicsContext
		virtual void Init(Window* window) override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_ContextWindow = nullptr;

		// Inherited via GraphicsContext
		virtual void SetupCamera(Camera* cam, bool isMainCam = true) override;
		virtual void SetupObject(Object* obj) override;
		virtual void RemoveObject(Object* obj) override;
		virtual void DrawObjects(std::vector<Object*>* objs) override;

		// Inherited via GraphicsContext
		virtual bool IsClosed() override;
		virtual int GetWidth() override;
		virtual int GetHeight() override;
	};
}