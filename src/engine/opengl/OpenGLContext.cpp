#include "OpenGLContext.h"

void engine::OpenGL1Context::Init(Window* window)
{
	m_ContextWindow = reinterpret_cast<GLFWwindow*>(window);

	glfwMakeContextCurrent(m_ContextWindow);
	gladLoadGL(glfwGetProcAddress);

	std::cout << " OPENGL CONTEXT CREATED SUCCESFULLY \n";
	std::cout << " CONTEXT RUNNING OPENGL1 \n";
	std::cout << "    Vendor    | " << reinterpret_cast<const char*> (glGetString(GL_VENDOR)) << "\n";
	std::cout << "     GPU      | " << reinterpret_cast<const char*> (glGetString(GL_RENDERER)) << "\n";
	std::cout << "  GL VERSION  | " << reinterpret_cast<const char*> (glGetString(GL_VERSION)) << "\n";

	// 3.30 OpenGL version. Not used for now.
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 30);
}

void engine::OpenGL1Context::SwapBuffers()
{
	glfwSwapBuffers(m_ContextWindow);
}

void engine::OpenGL1Context::SetupObject(Object* obj)
{
	std::cout << "OpenGL1Context::SetupObject not implemented \n";
}

void engine::OpenGL1Context::RemoveObject(Object* obj)
{
	std::cout << "OpenGL1Context::RemoveObject not implemented \n";
}

void engine::OpenGL1Context::DrawObjects(std::vector<Object*>* objs)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glBegin(GL_TRIANGLES);

	for (auto obj : *objs)
	{
		const auto vertices = obj->GetMesh()->GetVertList();

		for (Vertex v : *vertices)
		{
			v.VertexPos = obj->GetModelMatrix() * v.VertexPos;

			auto color = obj->GetMesh()->GetMeshColor();
			glColor3f(v.VertexPos.x, v.VertexPos.y, v.VertexPos.z); //Purposefully inputted vertex position.
			glVertex3f(v.VertexPos.x, v.VertexPos.y, v.VertexPos.z);
		}
	}

	glEnd();

	SwapBuffers();
}

bool engine::OpenGL1Context::IsClosed()
{
	return false;
}

int engine::OpenGL1Context::GetWidth()
{
	return 0;
}

int engine::OpenGL1Context::GetHeight()
{
	return 0;
}

//void GL1Render::DrawObjects(const std::vector<Object*>* objects)
//{
//	glm::vec4 color(1.f, 1.f, 1.f, 1.f);
//	glBegin(GL_TRIANGLES);
//	glColor3f(color.r, color.g, color.b);
//	for (Object* object : *(objects))
//	{
//		for (Vertex vertex : *(object->GetMesh()->GetVertList()))
//		{
//			vertex.position = object->GetModelMatrix() * vertex.position;
//			glColor3f(vertex.color.r, vertex.color.g, vertex.color.b);
//			glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
//		}
//	}
//	glEnd();
//}